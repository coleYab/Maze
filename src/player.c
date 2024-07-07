#include "../headers/game.h"
#include <SDL2/SDL_keyboard.h>

/**
 * move_player - function to move the player through the maze.
 *
 * @player: the player to move.
 */
void move_player(Player_t *player)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	double oldDirX, oldPlaneX;

	if (state[SDL_SCANCODE_W])
	{
		if (WorldMap[(int)(player->posX + player->dirX * MOVING_SPEED
			)][(int)(player->posY)] == 0)
			player->posX += player->dirX * MOVING_SPEED;
		if (WorldMap[(int)(player->posX)][(int)(
			player->posY + player->dirY * MOVING_SPEED)] == 0)
			player->posY += player->dirY * MOVING_SPEED;
	}
	if (state[SDL_SCANCODE_S])
	{
		if (WorldMap[(int)(player->posX - player->dirX * MOVING_SPEED
			)][(int)(player->posY)] == 0)
			player->posX -= player->dirX * MOVING_SPEED;
		if (WorldMap[(int)(player->posX)][(int)(
			player->posY - player->dirY * MOVING_SPEED)] == 0)
			player->posY -= player->dirY * MOVING_SPEED;
	}
	if (state[SDL_SCANCODE_A])
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
	if (state[SDL_SCANCODE_D])
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
