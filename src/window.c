#include "../headers/main.h"
#include <stdio.h>

/**
 * leave_game - deallocates all the game resources.
 *
 * @gw: game window.
 * @exit_status: the exit status for the window.
 */
void leave_game(GameWindow_t *gw, int exit_status)
{
	if (gw->renderer)
		SDL_DestroyRenderer(gw->renderer);
	if (gw->window)
		SDL_DestroyWindow(gw->window);

	IMG_Quit();

	SDL_Quit();

	exit(exit_status);
}

/**
 * init_game - function that will initialize all the game resources.
 *
 * @gw: game window.
 */
void init_game(GameWindow_t *gw)
{
	if ((SDL_Init(SDL_INIT_VIDEO) != 0) &&
		((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG))
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
		leave_game(gw, EXIT_FAILURE);
	}
}

/**
 * render - renders a texture into the winodw.
 *
 * @gw: game window type.
 * @texture: the texture to be rendered.
 */
void render(GameWindow_t *gw, SDL_Texture *texture)
{
	SDL_UpdateTexture(texture, NULL, gw->buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(gw->renderer);
	SDL_RenderCopy(gw->renderer, texture, NULL, NULL);
	SDL_RenderPresent(gw->renderer);
}
