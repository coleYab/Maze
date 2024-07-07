#ifndef __GAME_MAP
#define __GAME_MAP

#include "window.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

extern int WorldMap[MAP_HEIGHT][MAP_WIDTH];

void draw_world(GameWindow_t *gw, Player_t *player);

#endif