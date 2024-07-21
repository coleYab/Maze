#include "../headers/main.h"

/**
 * manage_current_texture - sets the horizontal line a specific value.
 *
 * @raycaster: the raycaster struct.
 * @player: the player struct.
 * @gw: the game window.
 * @x: the x co-ordinate to be rendered.
 */
void manage_current_texture(RayCaster_t *raycaster,
				Player_t *player, GameWindow_t *gw, int x)
{
	int texNum, texX, texY;
	double wallX, step, texPos;
	Uint32 color;

	texNum = raycaster->map->map[player->mapX][player->mapY] - 1;
	if (raycaster->side == 0)
		wallX = (player->posY + raycaster->perpWallDist
					* raycaster->rayDirY);
	else
		wallX = (player->posX + raycaster->perpWallDist
					* raycaster->rayDirX);

	wallX -= floor((wallX));
	texX = (int)(wallX * (double)(TEXTURE_WIDTH));

	if (raycaster->side == 0 && raycaster->rayDirX > 0)
		texX = TEXTURE_WIDTH - texX - 1;
	if (raycaster->side == 1 && raycaster->rayDirY < 0)
		texX = TEXTURE_WIDTH - texX - 1;

	step = 1.0 * TEXTURE_HEIGHT / raycaster->lineHeight;
	texPos = (raycaster->drawStart - SCREEN_HEIGHT / 2
				+ raycaster->lineHeight / 2) * step;
	for (int y = raycaster->drawStart; y < raycaster->drawEnd; y++)
	{
		texY = (int)texPos & (TEXTURE_HEIGHT - 1);
		texPos += step;
		color = gw->gt->texture[texNum][TEXTURE_WIDTH * texY + texX];
		/* making the color darker */
		if (raycaster->side == 1)
			color = (color >> 1) & 8355711;
		gw->buffer[y][x] = color;
	}
}

/**
 * draw_walls - draw the walls using raycasting.
 *
 * @gw: game window.
 * @player: player.
 * @raycaster: the raycaster variables struct.
 */
void draw_walls(GameWindow_t *gw, Player_t *player,
				RayCaster_t *raycaster)
{
	int x;

	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		set_horizontal_raycaster_values(raycaster, player, x);
		cast_rays(raycaster, player);
		manage_current_texture(raycaster, player, gw, x);
	}
}

/**
 * draw_world - draw the world using raycasting.
 *
 * @gw: game window.
 * @player: player.
 * @map: the map for the player.
 */
void draw_world(GameWindow_t *gw, Player_t *player, Map_t *map)
{
	RayCaster_t raycaster;

	raycaster.map = map;

	draw_floor_celling(gw, player);
	draw_walls(gw, player, &raycaster);
}
