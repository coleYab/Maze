#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "structs.h"

void run(Game_t *game);
void game_loop(GameWindow_t *gw, Player_t *player, Map_t *map);
void exit_gae(Game_t *game);
Uint32 get_color_from_map(int **map, int mapX, int mapY);
void reset_game_buffer(GameWindow_t *gw);
void draw_vertical_line(GameWindow_t *gw, int x, int start, int end, Uint32 color);
Uint32 rgb(Uint8 r, Uint8 g, Uint8 b);
extern int WorldMap[MAP_HEIGHT][MAP_WIDTH];
Map_t* parse_map(const char *file_name);
void draw_minimap(GameWindow_t *gw, Player_t *player, Map_t *map);
void parse_game_map(int argc, char *argv[], Map_t *map);
void draw_world(GameWindow_t *gw, Player_t *player, Map_t *map);
void free_map(Map_t *map);
void move_player(GameWindow_t *, Player_t *);
void allocate_textures(GameTexture_t *);
void free_textures(GameTexture_t *);
void init_game(GameWindow_t *gw);
void destroy_game(GameWindow_t *gw);
void render(GameWindow_t *gw, SDL_Texture *);

#endif
