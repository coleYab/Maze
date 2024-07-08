#include "../headers/game.h"

/**
 * set_horizontal_raycaster_values - sets values for the horizontal.
 *
 * @raycaster: the raycaster thing.
 * @player: the player.
 * @x: the x value.
 */
void set_horizontal_raycaster_values(
	RayCaster_t *raycaster, Player_t *player, int x)
{
	player->cameraX = 2 * x / (double)(SCREEN_WIDTH) - 1, raycaster->hit = 0;
	raycaster->rayDirX = player->dirX + player->planeX * player->cameraX;
	player->mapX = (int)(player->posX);
	raycaster->rayDirY = player->dirY + player->planeY * player->cameraX;
	player->mapY = (int)(player->posY);

	raycaster->deltaDistX = (raycaster->rayDirX == 0
		) ? 1e30 : fabs(1 / raycaster->rayDirX);
	raycaster->deltaDistY = (raycaster->rayDirY == 0
		) ? 1e30 : fabs(1 / raycaster->rayDirY);

	if (raycaster->rayDirX < 0)
		raycaster->stepX = -1, raycaster->sideDistX = (
			player->posX - player->mapX) * raycaster->deltaDistX;
	else
		raycaster->stepX = 1, raycaster->sideDistX = (
			player->mapX + 1.0 - player->posX) * raycaster->deltaDistX;
	if (raycaster->rayDirY < 0)
		raycaster->stepY = -1,	raycaster->sideDistY = (
			player->posY - player->mapY) * raycaster->deltaDistY;
	else
		raycaster->stepY = 1, raycaster->sideDistY = (
			player->mapY + 1.0 - player->posY) * raycaster->deltaDistY;
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
	{
		if (raycaster->sideDistX < raycaster->sideDistY)
			raycaster->sideDistX += raycaster->deltaDistX,
			player->mapX += raycaster->stepX, raycaster->side = 0;

		else
			raycaster->sideDistY += raycaster->deltaDistY,
			player->mapY += raycaster->stepY, raycaster->side = 1;

		if (raycaster->map->map[player->mapX][player->mapY] > 0)
			raycaster->hit = 1;
	}

	if (raycaster->side == 0)
		raycaster->perpWallDist = (
			player->mapX - player->posX + (1 - raycaster->stepX) / 2
			) / raycaster->rayDirX;
	else
		raycaster->perpWallDist = (
				player->mapY - player->posY + (1 - raycaster->stepY) / 2
			) / raycaster->rayDirY;

	raycaster->lineHeight = (int)(SCREEN_HEIGHT / raycaster->perpWallDist);

	raycaster->drawStart = -raycaster->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (raycaster->drawStart < 0)
		raycaster->drawStart = 0;

	raycaster->drawEnd = raycaster->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (raycaster->drawEnd >= SCREEN_HEIGHT)
		raycaster->drawEnd = SCREEN_HEIGHT - 1;
}

/**
 * draw_world - draw the world by using raycasting.
 *
 * @gw: game window.
 * @player: player.
 * @map: the map for the player.
*/
void draw_world(GameWindow_t *gw, Player_t *player, Map_t *map)
{
	RayCaster_t raycaster;
	Uint32 color = rgb(122, 122, 122);

	raycaster.map = map;
	for (int y = 0; y < SCREEN_HEIGHT; y++)
	{
		float rayDirX0 = player->dirX - player->planeX;
		float rayDirY0 = player->dirY - player->planeY;
		float rayDirX1 = player->dirX + player->planeX;
		float rayDirY1 = player->dirY + player->planeY;
		int p = y - SCREEN_HEIGHT / 2;
		float posZ = 0.5 * SCREEN_HEIGHT;
		float rowDistance = posZ / p;
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
		float floorX = player->posX + rowDistance * rayDirX0;
		float floorY = player->posY + rowDistance * rayDirY0;

		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			floorX += floorStepX;
			floorY += floorStepY;
			gw->buffer[y][x] = color;
			gw->buffer[SCREEN_HEIGHT - y - 1][x] = color;
		}
	}

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		set_horizontal_raycaster_values(&raycaster, player, x);
		cast_rays(&raycaster, player);
		color = get_color_from_map(map->map, player->mapX, player->mapY);
		if (raycaster.side == 1)
			color /= 1.14;
		draw_vertical_line(
			gw, x, raycaster.drawStart, raycaster.drawEnd, color);
	}
}
