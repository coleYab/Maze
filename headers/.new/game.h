#ifndef __GAME_H
#define __GAME_H

#include "map.h"
#include "player.h"
#include "helpers.h"
#include "window.h"
#include "raycaster.h"
#include "textures.h"

// typedef struct {
//     GameWindow_t *gw;
//     Map_t *map;
//     Player_t *player;
//     GameTexture_t *texture;
// } Game_t;

// void run(Game_t *game);
void game_loop(GameWindow_t *gw, Player_t *player, Map_t *map);
// void exit_gae(Game_t *game);

#endif