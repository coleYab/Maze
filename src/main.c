#include "../headers/main.h"

/**
 * main - entry point for the game.
 *
 * @argc: argument count.
 * @argv: argument vector.
 *
 * Return: 1 - in failure otherwise 0.
 */
int main(int argc, char *argv[])
{
	GameWindow_t gw = {NULL, NULL, false, {{0}}, NULL, true, {0}, GAME_START};
	Map_t map = {NULL, 0, 0};
	Player_t player = {
		22.0, 11.5, /* posn*/
		-1.0, 0.0, /* direction */
		0.0, 0.66, /* plane */
		0.0, 0.0,
		0, 0
	};
	GameTexture_t gt = {NULL};

	gw.gt = &gt;
	parse_game_map(argc, argv, &map);
	allocate_textures(&gt);
	init_game(&gw);
	game_loop(&gw, &player, &map);
	free_textures(&gt);
	free_map(&map);
	leave_game(&gw, EXIT_SUCCESS);

	return (EXIT_SUCCESS);
}
