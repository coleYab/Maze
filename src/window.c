#include "../headers/window.h"
#include <stdio.h>

/**
 * destroy_game - deallocates all the game resources.
 *
 * @gw: game window.
 */
void destroy_game(GameWindow_t *gw)
{
	if (gw->renderer)
		SDL_DestroyRenderer(gw->renderer);
	if (gw->window)
		SDL_DestroyWindow(gw->window);

	SDL_Quit();
}

/**
 * init_game - function that will initialize all the game resources.
 *
 * @gw: game window.
 */
void init_game(GameWindow_t *gw)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		exit(1);
	}

	gw->instantiated = true;
	gw->window = SDL_CreateWindow(
		"Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN);

	if (gw->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	gw->renderer = SDL_CreateRenderer(
		gw->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gw->renderer == NULL)
	{
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		destroy_game(gw);
		exit(1);
	}
}
