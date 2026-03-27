#include <3ds.h>
#include <citro2d.h>
#include "menus/components/ui_element.h"
#include "menus/components/ui_screen.h"
#include "math_helpers.h"
#include "menus/components/ui_list.h"
#include "menus/components/ui_window.h"
#include "menus/components/ui_textbox.h"
#include "menus/components/ui_image.h"
#include "fonts/bigFont.h"
#include "main.h"
#include "easing.h"
#include "color_channels.h"
#include "mp3_player.h"
#include "graphics.h"
#include "main_menu.h"
#include "level_select.h"

#include "gameplay.h"

#include "save/config.h"

static UIScreen screen;
static UIElement *bg_gradient;


static UIAction actions[] = {

};

void gameplay_screen_init() {
    ui_load_screen(&screen, actions, sizeof(actions) / sizeof(actions[0]), "romfs:/menus/gameplay.txt");
    bg_gradient = ui_get_element_by_tag(&screen, "gradient");
}

int gameplay_screen_loop() {
    UIInput touch;
    touchPosition touchPos;
    hidTouchRead(&touchPos);

    ColorChannel channel = channels[CHANNEL_BG];
    Color color = channel.color;

    ui_image_set_tint(bg_gradient, C2D_Color32(color.r, color.g, color.b, 255));

    touch.touchPosition = touchPos;
    touch.did_something = false;
    touch.interacted = false;
    ui_screen_update(&screen, &touch);

    ui_screen_draw(&screen);

    return false;
}