#ifndef __HELPERS_H
#define __HELPERs_H

#include <stddef.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "window.h"

Uint32 get_color_from_map(int mapX, int mapY);
void reset_game_buffer(GameWindow_t *gw);
void draw_vertical_line(GameWindow_t *gw, int x, int start, int end, Uint32 color);
Uint32 rgb(Uint8 r, Uint8 g, Uint8 b);

#endif
