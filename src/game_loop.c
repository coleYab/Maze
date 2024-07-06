#include "../headers/window.h"
#include <stdbool.h>

/**
 * is_exit_event - checks if the user wants to exit the program.
 *
 * @event: the event to be polled.
 *
 * Return: true if the user wants to exit otherwise false.
 */
bool is_exit_event(SDL_Event *event)
{
	if (event)
	{
		while (SDL_PollEvent(event))
		{
			if (event->type == SDL_QUIT)
				return (true);
		}
	}

	return (false);
}


/**
 * game_loop - main game loop that will run the
 *              whole game.
 *
 * @gw: it is game window.
 */
void game_loop(GameWindow_t *gw)
{
	bool running = true;
	SDL_Event event;
		SDL_Texture *texture = SDL_CreateTexture(
			gw->renderer, SDL_PIXELFORMAT_ABGR8888,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH, SCREEN_HEIGHT
		);

	while (running)
	{
		render(gw, texture);
		SDL_Delay(16);
		running = !is_exit_event(&event);
	}

	SDL_DestroyTexture(texture);
}
