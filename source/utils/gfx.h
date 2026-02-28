#pragma once
#include <3ds.h>
#include <citro2d.h>

void draw_9_slice(const C2D_Image atlas, const float x, const float y, const int width, const int height, const float border, const u32 color);
Tex3DS_SubTexture select_box(const C2D_Image *image, int x, int y, int endX, int endY);
void set_scissor(GPU_SCISSORMODE mode, int x, int y, int width, int height);
