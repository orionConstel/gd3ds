#include "ui_screen.h"
#include "ui_element.h"
#include "ui_button.h"
#include "ui_image.h"
#include "ui_screen.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <citro2d.h>

void ui_screen_update(UIScreen* s, touchPosition* touch) {
    for (int i = 0; i < s->count; i++)
        s->elements[i].update(&s->elements[i], touch);
}

void ui_screen_draw(UIScreen* s) {
    for (int i = 0; i < s->count; i++)
        s->elements[i].draw(&s->elements[i]);
}

UIActionFn ui_find_action(const UIAction* actions, size_t count, const char* name) {
    for (size_t i = 0; i < count; i++)
        if (strcmp(actions[i].name, name) == 0)
            return actions[i].fn;
    return NULL;
}

static void trim_newline(char* s) {
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}


static void strip_quotes(char* s) {
    size_t len = strlen(s);
    if (len >= 2 && s[0] == '"' && s[len - 1] == '"') {
        memmove(s, s + 1, len - 1);
        s[len - 2] = '\0';
    }
}

static char* next_token(char** cursor)
{
    if (!*cursor) return NULL;

    char* s = *cursor;

    // Skip leading spaces
    while (*s == ' ') s++;

    if (*s == '\0') {
        *cursor = NULL;
        return NULL;
    }

    char* start = s;
    int inQuotes = 0;

    while (*s) {
        if (*s == '"') {
            inQuotes = !inQuotes;
        }
        else if ((*s == ' ' || *s == '\n' || *s == '\r') && !inQuotes) {
            break;
        }
        s++;
    }

    if (*s) {
        *s = '\0';
        *cursor = s + 1;
    } else {
        *cursor = NULL;
    }

    return start;
}


void ui_load_screen(UIScreen* screen,
                    const UIAction* actions,
                    size_t actionCount,
                    const char* path)
{
    FILE* f = fopen(path, "r");
    if (!f) return;

    screen->count = 0;

    char line[256];

    while (fgets(line, sizeof(line), f)) {

        trim_newline(line);

        if (line[0] == '#' || line[0] == '\0')
            continue;
        
        char* cursor = line;
        char* token = next_token(&cursor);
        if (!token) continue;

        char type[16];
        strcpy(type, token);

        // Defaults (optional values)
        int x = 0, y = 0, id = 0;
        float sx = 1.0f, sy = 1.0f;
        char actionName[64] = {0};

        char text[64] = {0};

        // Parse key=value pairs
        while ((token = next_token(&cursor)) != NULL) {
            char* equal = strchr(token, '=');
            if (!equal) continue;

            *equal = '\0';

            char* key = token;
            char* value = equal + 1;


            if (strcmp(key, "x") == 0)
                x = atoi(value);
            else if (strcmp(key, "y") == 0)
                y = atoi(value);
            else if (strcmp(key, "id") == 0)
                id = atoi(value);
            else if (strcmp(key, "sx") == 0)
                sx = atof(value);
            else if (strcmp(key, "sy") == 0)
                sy = atof(value);
            else if (strcmp(key, "action") == 0) {
                strip_quotes(value);
                strncpy(actionName, value, 63);
            } else if (strcmp(key, "text") == 0) {
                strip_quotes(value);
                strncpy(text, value, 63);
            }
        }

        if (screen->count >= UI_MAX_ELEMENTS)
            break;

        if (strcmp(type, "button") == 0) {
            screen->elements[screen->count++] =
                ui_create_button(
                    x, y, id,
                    ui_find_action(actions, actionCount, actionName),
                    NULL,
                    text
                );
        }

        else if (strcmp(type, "image") == 0) {

            screen->elements[screen->count++] =
                ui_create_image(x, y, id, sx, sy);
        }
    }

    fclose(f);
}
