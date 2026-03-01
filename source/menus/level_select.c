#include <3ds.h>
#include <citro2d.h>
#include "menus/components/ui_element.h"
#include "menus/components/ui_screen.h"
#include "math_helpers.h"
#include "menus/components/ui_list.h"
#include "menus/components/ui_window.h"
#include "menus/components/ui_textbox.h"
#include "menus/components/ui_image.h"

UIScreen screen;

volatile bool start_level = false;

void action_open_level(void* data) { 
	start_level = true; 
};

void action_open_win0(void* data) { 
	ui_run_func_on_tag(&screen, "win0", ui_enable_element);
};

void action_close_win0(void* data) { 
	ui_run_func_on_tag(&screen, "win0", ui_disable_element);
};

UIAction actions[] = {
    {"open_level", action_open_level},
    {"open_win0", action_open_win0},
    {"close_win0", action_close_win0}
};

UIElement *bg_gradient = NULL;
UIElement *level_card_window = NULL;

void level_select_loop() {
	C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	ui_load_screen(&screen, actions, sizeof(actions) / sizeof(actions[0]), "romfs:/menus/level_select.txt");

	// Set bg color
	bg_gradient = ui_get_element_by_tag(&screen, "gradient");
	ui_image_set_tint(bg_gradient, C2D_Color32(0, 0, 234, 255));
	
	// Set bg color
	level_card_window = ui_get_element_by_tag(&screen, "card_window");
	ui_window_set_tint(level_card_window, C2D_Color32(0, 0, 0, 127));

	while (aptMainLoop()) {
		hidScanInput();
        
		if (start_level) break;

		UIInput touch;
		touchPosition touchPos;
		hidTouchRead(&touchPos);
		touch.touchPosition = touchPos;
		touch.did_something = false;
		touch.interacted = false;

		ui_screen_update(&screen, &touch);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(bot, C2D_Color32(0, 0, 0, 255));
        C2D_SceneBegin(bot);

		ui_screen_draw(&screen);
		
		C3D_FrameEnd(0);
	}
}