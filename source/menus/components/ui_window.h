#pragma once
#include "ui_element.h"
void ui_window_set_tint(UIElement* e, u32 color);
UIElement ui_create_window(
    int x, int y, int w, int h, int style,
    char (*tag)[TAG_LENGTH]
);