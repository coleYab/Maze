#include "../headers/main.h"
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
 * @player: the player.
 * @map: the map to be used.
 */
void game_loop(GameWindow_t *gw, Player_t *player, Map_t *map)
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
		reset_game_buffer(gw);
		handle_keyboard(gw, map, player);
		draw_world(gw, player, map);
		if (gw->display_map)
			draw_minimap(gw, player, map);
		render(gw, texture);
		SDL_Delay(16);
		running = (!is_exit_event(&event)) && (gw->game_state != GAME_END);
	}

	SDL_DestroyTexture(texture);
}
