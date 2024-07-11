#include "../headers/main.h"
#include <SDL2/SDL_keyboard.h>

/**
 * rotate - function to rotate the player through the maze.
 *
 * @gw: game window.
 * @map: map to do.
 * @player: the player to move.
 * @flag: is he rotating left.
 */
void rotate(GameWindow_t *gw, Map_t *map, Player_t *player,
	int flag)
{
	double oldDirX = 0, oldPlaneX = 0;

	(void)map;
	(void)gw;
	if (flag)
	{
		oldDirX = player->dirX;
		player->dirX = player->dirX * cos(ROTATION_SPEED
			) - player->dirY * sin(ROTATION_SPEED);
		player->dirY = oldDirX * sin(ROTATION_SPEED
			) + player->dirY * cos(ROTATION_SPEED);
		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(ROTATION_SPEED
			) - player->planeY * sin(ROTATION_SPEED);
		player->planeY = oldPlaneX * sin(ROTATION_SPEED
			) + player->planeY * cos(ROTATION_SPEED);
	}
	else
	{
		oldDirX = player->dirX;
		player->dirX = player->dirX * cos(-ROTATION_SPEED
			) - player->dirY * sin(-ROTATION_SPEED);
		player->dirY = oldDirX * sin(-ROTATION_SPEED
			) + player->dirY * cos(-ROTATION_SPEED);
		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(-ROTATION_SPEED
			) - player->planeY * sin(-ROTATION_SPEED);
		player->planeY = oldPlaneX * sin(-ROTATION_SPEED
			) + player->planeY * cos(-ROTATION_SPEED);
	}
}

/**
 * move_player - function to move the player through the maze.
 *
 * @gw: game window.
 * @map: map to use.
 * @player: the player to move.
 * @flag: is he moving forward?
 */
void move_player(GameWindow_t *gw, Map_t *map, Player_t *player,
	int flag)
{
	(void)gw;
	if (flag)
	{
		if (map->map[(int)(player->posX + player->dirX * MOVING_SPEED
			)][(int)(player->posY)] == 0)
			player->posX += player->dirX * MOVING_SPEED;
		if (map->map[(int)(player->posX)][(int)(
			player->posY + player->dirY * MOVING_SPEED)] == 0)
			player->posY += player->dirY * MOVING_SPEED;
	}
	else
	{
		if (map->map[(int)(player->posX - player->dirX * MOVING_SPEED
			)][(int)(player->posY)] == 0)
			player->posX -= player->dirX * MOVING_SPEED;
		if (map->map[(int)(player->posX)][(int)(
			player->posY - player->dirY * MOVING_SPEED)] == 0)
			player->posY -= player->dirY * MOVING_SPEED;
	}
}

/**
 * handle_keyboard - function to move the player through the maze.
 *
 * @gw: game window.
 * @map: map_to_be_used.
 * @player: the player to move.
 */
void handle_keyboard(GameWindow_t *gw, Map_t *map, Player_t *player)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if ((state[SDL_SCANCODE_W]) || (state[SDL_SCANCODE_S]))
		move_player(gw, map, player, state[SDL_SCANCODE_W]);

	if ((state[SDL_SCANCODE_A]) || (state[SDL_SCANCODE_D]))
		rotate(gw, map, player, state[SDL_SCANCODE_A]);

	if (state[SDL_SCANCODE_M] && (state[SDL_SCANCODE_LCTRL] ||
		state[SDL_SCANCODE_RCTRL]))
		gw->display_map = !(gw->display_map);

	if (state[SDL_SCANCODE_B])
		gw->game_state = GAME_PLAYING;

	if (state[SDL_SCANCODE_ESCAPE])
		gw->game_state = GAME_END;
}
