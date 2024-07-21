#include "../headers/main.h"


/**
 * set_horizontal_raycaster_values - sets values for the horizontal.
 *
 * @raycaster: the raycaster struct.
 * @player: the player.
 * @x: the x value.
 */
void set_horizontal_raycaster_values(
	RayCaster_t *raycaster, Player_t *player, int x)
{
	player->cameraX = 2 * x / (double)(SCREEN_WIDTH) - 1;
	raycaster->hit = 0;
	player->mapX = (int)(player->posX);
	player->mapY = (int)(player->posY);
	raycaster->rayDirX = player->dirX + player->planeX * player->cameraX;
	raycaster->rayDirY = player->dirY + player->planeY * player->cameraX;

	raycaster->deltaDistX = ((raycaster->rayDirX == 0) ? 1e30 :
					fabs(1 / raycaster->rayDirX));
	raycaster->deltaDistY = ((raycaster->rayDirY == 0) ? 1e30 :
					fabs(1 / raycaster->rayDirY));

	if (raycaster->rayDirX < 0)
	{
		raycaster->stepX = -1;
		raycaster->sideDistX = ((player->posX - player->mapX
						) * raycaster->deltaDistX);
	}
	else
	{
		raycaster->stepX = 1;
		raycaster->sideDistX = ((player->mapX + 1.0 - player->posX
						) * raycaster->deltaDistX);
	}

	if (raycaster->rayDirY < 0)
	{
		raycaster->stepY = -1;
		raycaster->sideDistY = ((player->posY - player->mapY
						) * raycaster->deltaDistY);
	}
	else
	{
		raycaster->stepY = 1;
		raycaster->sideDistY = ((player->mapY + 1.0 - player->posY
						) * raycaster->deltaDistY);
	}
}

/**
 * cast_to_next_block - casts a ray to the next block.
 *
 * @raycaster: the holder for variables used in raycasting.
 * @player: the current player.
 */
void cast_to_next_block(RayCaster_t *raycaster, Player_t *player)
{
	if (raycaster && player)
	{
		if (raycaster->sideDistX < raycaster->sideDistY)
		{
			raycaster->sideDistX += raycaster->deltaDistX;
			player->mapX += raycaster->stepX;
			raycaster->side = 0;
		}
		else
		{
			raycaster->sideDistY += raycaster->deltaDistY;
			player->mapY += raycaster->stepY;
			raycaster->side = 1;
		}

		if (raycaster->map->map[player->mapX][player->mapY] > 0)
			raycaster->hit = 1;
	}
}

/**
 * cast_rays - cast rays to the wall.
 *
 * @raycaster: the raycaster struct.
 * @player: the player.
 */
void cast_rays(RayCaster_t *raycaster, Player_t *player)
{
	while (raycaster->hit == 0)
		cast_to_next_block(raycaster, player);

	if (raycaster->side == 0)
		raycaster->perpWallDist = (player->mapX - player->posX +
					(1 - raycaster->stepX) / 2) / raycaster->rayDirX;
	else
		raycaster->perpWallDist = (player->mapY - player->posY +
					(1 - raycaster->stepY) / 2) / raycaster->rayDirY;

	raycaster->lineHeight = (int)(SCREEN_HEIGHT / raycaster->perpWallDist);

	raycaster->drawStart = -raycaster->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (raycaster->drawStart < 0)
		raycaster->drawStart = 0;

	raycaster->drawEnd = raycaster->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (raycaster->drawEnd >= SCREEN_HEIGHT)
		raycaster->drawEnd = SCREEN_HEIGHT - 1;
}

/**
 * draw_floor_celling - draw the world using raycasting.
 *
 * @gw: game window.
 * @player: player.
 */
void draw_floor_celling(GameWindow_t *gw, Player_t *player)
{
	Uint32 color;
	int p, cellX, cellY, tx, ty, floorTexture, ceilingTexture;
	float rayDirX0, rayDirY0, rayDirX1, rayDirY1, posZ, rowDistance,
		floorStepX, floorStepY, floorX, floorY;

	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		rayDirX0 = player->dirX - player->planeX;
		rayDirY0 = player->dirY - player->planeY;
		rayDirX1 = player->dirX + player->planeX;
		rayDirY1 = player->dirY + player->planeY;
		p = y - SCREEN_HEIGHT / 2, posZ = 0.5 * SCREEN_HEIGHT;
		rowDistance = posZ / p;
		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
		floorX = player->posX + rowDistance * rayDirX0;
		floorY = player->posY + rowDistance * rayDirY0;

		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			cellX = (int)(floorX), cellY = (int)(floorY);

			tx = (int)(TEXTURE_WIDTH * (floorX - cellX)) & (TEXTURE_WIDTH - 1);
			ty = (int)(TEXTURE_HEIGHT * (floorY - cellY)) & (TEXTURE_HEIGHT - 1);

			floorX += floorStepX, floorY += floorStepY;
			floorTexture = 3, ceilingTexture = 6;

			/* rendering the floor */
			color = gw->gt->texture[floorTexture][TEXTURE_WIDTH * ty + tx];
			gw->buffer[y][x] = ((color >> 1) & 8355711);

			/* rendering the floor */
			color = gw->gt->texture[ceilingTexture][TEXTURE_WIDTH * ty + tx];
			gw->buffer[SCREEN_HEIGHT - y - 1][x] = ((color >> 1) & 8355711);
		}
	}
}
