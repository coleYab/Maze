#include <stdio.h>
#include "../headers/window.h"

/**
 * main - entry point for the game.
 *
 * Return: 1 - in failure otherwise 0.
 */
int main(void)
{
	GameWindow_t gw = {NULL, NULL, false, {{0}}};

	init_game(&gw);
	game_loop(&gw);
	destroy_game(&gw);

	return (EXIT_SUCCESS);
}
