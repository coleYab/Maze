#include "../headers/main.h"
#include <SDL2/SDL.h>

/**
 * game_loop - main game loop that runs our game.
 */
void game_loop()
{
	bool running = true;
	SDL_Event event;

	while (running)
	{
		reset_game_buffer();
		running = is_exit_event(&event);
		move_player();
		draw_world();
		render(screen.renderer, screen.texture);
		SDL_Delay(16);
	}
}
