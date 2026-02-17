#include <3ds.h>
#include <citro2d.h>
#include "menus/components/ui_element.h"
#include "menus/components/ui_screen.h"
#include "math_helpers.h"

volatile bool start_level = false;

void action_hi(void* data) { start_level = true; };

UIAction actions[] = {
    {"hibykrmal", action_hi}
};

void level_select_loop() {
	UIScreen screen;
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	C3D_RenderTargetClear(top, C3D_CLEAR_ALL, 0, 0);

	ui_load_screen(&screen, actions, sizeof(actions) / sizeof(actions[0]), "romfs:/menus/level_select.txt");
	
	while (aptMainLoop()) {
		hidScanInput();
        
		if (start_level) break;

		touchPosition touch;
		hidTouchRead(&touch);
		ui_screen_update(&screen, &touch);

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C3D_RenderTargetClear(top, C3D_CLEAR_ALL, RGBA8(3, 177, 255, 255), 0);
        C2D_SceneBegin(top);
		ui_screen_draw(&screen);
		
		C3D_FrameEnd(0);
	}
}