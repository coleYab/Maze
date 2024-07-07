#ifndef __GAME_WINDOW
#define __GAME_WINDOW

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "player.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720

typedef struct GameWindow
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool instantiated;
    Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
} GameWindow_t;

void init_game(GameWindow_t *gw);
void destroy_game(GameWindow_t *gw);
void game_loop(GameWindow_t *gw, Player_t *player);
void render(GameWindow_t *gw, SDL_Texture *);

#endif
