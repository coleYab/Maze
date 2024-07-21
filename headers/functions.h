#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "structs.h"

/*********************************************************************
 * Main game functions and helpers
 **********************************************************************/
void game_loop(GameWindow_t *gw, Player_t *player, Map_t *map);
void reset_game_buffer(GameWindow_t *gw);
void draw_vertical_line(GameWindow_t *gw, int x, int start,
	int end, Uint32 color);
Uint32 rgb(Uint8 r, Uint8 g, Uint8 b);
Map_t *parse_map(const char *file_name);

/*********************************************************************
 * Map Drawers helper functions
 **********************************************************************/
void draw_minimap(GameWindow_t *gw, Player_t *player, Map_t *map);
void parse_game_map(int argc, char *argv[], Map_t *map);
void draw_world(GameWindow_t *gw, Player_t *player, Map_t *map);
void free_map(Map_t *map);
void allocate_textures(GameTexture_t *);

/*********************************************************************
 * GameWindow helper functions
 **********************************************************************/
void free_textures(GameTexture_t *);
void init_game(GameWindow_t *gw);
void leave_game(GameWindow_t *gw, int exit_status);
void render(GameWindow_t *gw, SDL_Texture *);
void handle_keyboard(GameWindow_t *gw, Map_t *map, Player_t *player);


/*********************************************************************
 * Raycaster helper functions
 **********************************************************************/
void draw_floor_celling(GameWindow_t *gw, Player_t *player);
void cast_rays(RayCaster_t *raycaster, Player_t *player);
void cast_to_next_block(RayCaster_t *raycaster, Player_t *player);
void set_horizontal_raycaster_values(
	RayCaster_t *raycaster, Player_t *player, int x);

#endif
