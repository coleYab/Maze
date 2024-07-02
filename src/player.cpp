#include "../headers/main.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

/**
 * move_player - function to move the player through the maze.
 */
void move_player()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W])
	{
		if (world.worldMap[int(world.posX + world.dirX * moveSpeed)][int(world.posY)] == 0)
			world.posX += world.dirX * moveSpeed;
		if (world.worldMap[int(world.posX)][int(world.posY + world.dirY * moveSpeed)] == 0)
			world.posY += world.dirY * moveSpeed;
	}
	if (state[SDL_SCANCODE_S])
	{
		if (world.worldMap[int(world.posX - world.dirX * moveSpeed)][int(world.posY)] == 0)
			world.posX -= world.dirX * moveSpeed;
		if (world.worldMap[int(world.posX)][int(world.posY - world.dirY * moveSpeed)] == 0)
			world.posY -= world.dirY * moveSpeed;
	}
	if (state[SDL_SCANCODE_A])
	{
		double oldDirX = world.dirX;
		world.dirX = world.dirX * cos(rotSpeed) - world.dirY * sin(rotSpeed);
		world.dirY = oldDirX * sin(rotSpeed) + world.dirY * cos(rotSpeed);
		double oldPlaneX = world.planeX;
		world.planeX = world.planeX * cos(rotSpeed) - world.planeY * sin(rotSpeed);
		world.planeY = oldPlaneX * sin(rotSpeed) + world.planeY * cos(rotSpeed);
	}
	if (state[SDL_SCANCODE_D])
	{
		double oldDirX = world.dirX;
		world.dirX = world.dirX * cos(-rotSpeed) - world.dirY * sin(-rotSpeed);
		world.dirY = oldDirX * sin(-rotSpeed) + world.dirY * cos(-rotSpeed);
		double oldPlaneX = world.planeX;
		world.planeX = world.planeX * cos(-rotSpeed) - world.planeY * sin(-rotSpeed);
		world.planeY = oldPlaneX * sin(-rotSpeed) + world.planeY * cos(-rotSpeed);
	}
}


void draw_world()
{
	double cameraX, cameraY, rayDirX, rayDirY, sideDistX;
	double deltaDistX, deltaDistY, perpWallDist, sideDistY;
	int mapX, mapY, stepX, stepY, hit, side, lineHeight, drawStart, drawEnd;
	Uint32 color;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		cameraX = 2 * x / double(SCREEN_WIDTH) - 1, hit = 0;
		rayDirX = world.dirX + world.planeX * cameraX, mapX = int(world.posX);
		rayDirY = world.dirY + world.planeY * cameraX, mapY = int(world.posY);
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		if (rayDirX < 0)
			stepX = -1, sideDistX = (world.posX - mapX) * deltaDistX;
		else
			stepX = 1, sideDistX = (mapX + 1.0 - world.posX) * deltaDistX;
		if (rayDirY < 0)
			stepY = -1,	sideDistY = (world.posY - mapY) * deltaDistY;
		else
			stepY = 1, sideDistY = (mapY + 1.0 - world.posY) * deltaDistY;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
				sideDistX += deltaDistX, mapX += stepX, side = 0;
			else
				sideDistY += deltaDistY, mapY += stepY, side = 1;
			if (world.worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - world.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - world.posY + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;
		color = get_color_from_map(mapX, mapY);
		if (side == 1)
			color /= 1.14;
		drawVerticalLine(x, drawStart, drawEnd, color);
	}
}
