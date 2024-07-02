#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <vector>
#include "../headers/main.h"
#include <cmath>

World_t world = {
	{
		{0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4},
		{4, 0, 4, 0, 0, 0, 0, 4, 0, 4, 0, 4, 0, 4, 0, 4, 4, 0, 0, 0, 4, 4, 4, 4},
		{4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4},
		{4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 4, 4, 4, 4},
		{4, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
		{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 0, 0, 4, 0, 0, 0, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4},
		{4, 0, 4, 0, 4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4},
		{4, 0, 0, 4, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4},
		{4, 0, 4, 0, 4, 0, 0, 0, 0, 4, 4, 0, 4, 4, 0, 0, 4, 0, 0, 4, 0, 0, 0, 4},
		{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 4},
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}
	}, 22.0, 11.5, -1.0, 0.0, 0.0, 0.66
};


Screen_t screen = {nullptr, nullptr, nullptr, {{0}}};



void reset_game_buffer()
{
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH; ++x)
			screen.buffer[y][x] = 0;
	}
}

void drawMiniMap()
{
	SDL_Rect miniMapRect = {10, 10, mapWidth * miniMapScale, mapHeight * miniMapScale};
	SDL_SetRenderDrawColor(screen.renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(screen.renderer, &miniMapRect);

	// Draw the walls on the mini-map
	int rectWidth = miniMapScale;
	int rectHeight = miniMapScale;
	for (int y = 0; y < mapHeight; ++y)
	{
		for (int x = 0; x < mapWidth; ++x)
		{
			if (world.worldMap[x][y] > 0)
			{
				SDL_Rect wallRect = {10 + x * miniMapScale, 10 + y * miniMapScale, rectWidth, rectHeight};
				SDL_SetRenderDrawColor(screen.renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(screen.renderer, &wallRect);
			}
		}
	}

	// // Draw the player on the mini-map
	SDL_Rect playerRect = {10 + int(world.posX) * miniMapScale, 10 + int(world.posY) * miniMapScale, rectWidth / 5, rectHeight / 5};
	SDL_SetRenderDrawColor(screen.renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(screen.renderer, &playerRect);

	// Draw rays on the mini-map
	for (double x = 0; x < SCREEN_WIDTH; x++) // Adjust step size to reduce the number of lines drawn for clarity
	{
		double cameraX = 2 * x / double(SCREEN_WIDTH) - 1;
		double rayDirX = world.dirX + world.planeX * cameraX;
		double rayDirY = world.dirY + world.planeY * cameraX;

		double rayPosX = world.posX;
		double rayPosY = world.posY;

		int mapX = int(rayPosX);
		int mapY = int(rayPosY);

		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}

		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (world.worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

		int rayEndX = int(rayPosX + rayDirX * perpWallDist);
		int rayEndY = int(rayPosY + rayDirY * perpWallDist);

		SDL_SetRenderDrawColor(screen.renderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(screen.renderer, 10 + int(world.posX) * miniMapScale + miniMapScale / 2, 10 + int(world.posY) * miniMapScale + miniMapScale / 2,
						   10 + rayEndX * miniMapScale + miniMapScale / 2, 10 + rayEndY * miniMapScale + miniMapScale / 2);
	}
}


void drawVerticalLine(int x, int start, int end, Uint32 color)
{
	for (int y = start; y < end; y++)
	{
		screen.buffer[y][x] = color;
	}
}


Uint32 rgb(Uint8 r, Uint8 g, Uint8 b)
{
	return (r << 16) | (g << 8) | b;
}


Uint32 get_color_from_map(int mapX, int mapY)
{
	Uint32 color;
	switch (world.worldMap[mapX][mapY])
	{
	case 4:
		color = rgb(255, 0, 0);
		break;
	case 2:
		color = rgb(0, 255, 0);
		break;
	case 3:
		color = rgb(0, 0, 255);
		break;
	case 1:
		color = rgb(255, 255, 255);
		break;
	case 5:
		color = rgb(255, 255, 0);
		break;
	case 6:
		color = rgb(0, 255, 255);
		break;
	case 7:
		color = rgb(255, 0, 255);
		break;
	case 8:
		color = rgb(128, 128, 128);
		break;
	default:
		color = rgb(0, 0, 0);
		break;
	}

	return color;
}


int main(int argc, char *argv[])
{
	init_game();
	game_loop();
	destroy_game();
	return 0;
}
