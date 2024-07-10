#include "../headers/main.h"

/**
 * main - entry point for the game.
 *
 * Return: 1 - in failure otherwise 0.
 */
int main(int argc, char *argv[])
{
	GameWindow_t gw = {NULL, NULL, false, {{0}}, NULL, true, {0}};
	Map_t map = {NULL, 0, 0};
	Player_t player = {
		22.0, 11.5, /* posn*/
		-1.0, 0.0, /* direction */
		0.0, 0.66, /* plane */
		0.0, 0.0,
		0, 0
	};

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
		exit(1);
	GameTexture_t gt = {NULL};
	gw.gt = &gt;
	allocate_textures(&gt);
	parse_game_map(argc, argv, &map);
	init_game(&gw);
	game_loop(&gw, &player, &map);
	destroy_game(&gw);
	free_textures(&gt);
	free_map(&map);

	return (EXIT_SUCCESS);
}
