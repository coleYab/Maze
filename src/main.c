#include <stdio.h>
#include "../headers/game.h"

/**
 * main - entry point for the game.
 *
 * Return: 1 - in failure otherwise 0.
 */
int main(void)
{
	GameWindow_t gw = {NULL, NULL, false, {{0}}};
	Player_t player = {
		22.0, 11.5, /* posn*/
		-1.0, 0.0, /* direction */
		0.0, 0.66, /* plane */
		0.0, 0.0,
		0, 0
	};

	init_game(&gw);
	game_loop(&gw, &player);
	destroy_game(&gw);

	return (EXIT_SUCCESS);
}
