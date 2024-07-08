#ifndef __GAME_MAP
#define __GAME_MAP

#include "window.h"
#include "player.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define MINIMAP_SCALE 10  // Scale factor for the mini-map
#define MINIMAP_X_OFFSET 10  // X position of the mini-map
#define MINIMAP_Y_OFFSET 10  // Y position of the mini-map

typedef struct {
    int **map;
    int rows;
    int cols;
} Map_t;

extern int WorldMap[MAP_HEIGHT][MAP_WIDTH];

Map_t* parse_map(const char *file_name);
void draw_minimap(GameWindow_t *gw, Player_t *player, Map_t *map);
void parse_game_map(int argc, char *argv[], Map_t *map);
void draw_world(GameWindow_t *gw, Player_t *player, Map_t *map);
void free_map(Map_t *map);

#endif