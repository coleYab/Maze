#ifndef __GAME_H
#define __GAME_H

#include "map.h"
#include "player.h"
#include "helpers.h"
#include "window.h"
#include "raycaster.h"

typedef struct {
    GameWindow_t *gw;
    Map_t *map;
    Player_t *player;
} Game_t;

void game_loop(GameWindow_t *gw, Player_t *player, Map_t *map);

#endif