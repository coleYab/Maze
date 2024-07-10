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
    raycaster->rayDirX = player->dirX + player->planeX * player->cameraX;
    raycaster->rayDirY = player->dirY + player->planeY * player->cameraX;
    player->mapX = (int)(player->posX);
    player->mapY = (int)(player->posY);

    raycaster->deltaDistX = (raycaster->rayDirX == 0) ? 1e30 : fabs(1 / raycaster->rayDirX);
    raycaster->deltaDistY = (raycaster->rayDirY == 0) ? 1e30 : fabs(1 / raycaster->rayDirY);

    if (raycaster->rayDirX < 0)
    {
        raycaster->stepX = -1;
        raycaster->sideDistX = (player->posX - player->mapX) * raycaster->deltaDistX;
    }
    else
    {
        raycaster->stepX = 1;
        raycaster->sideDistX = (player->mapX + 1.0 - player->posX) * raycaster->deltaDistX;
    }

    if (raycaster->rayDirY < 0)
    {
        raycaster->stepY = -1;
        raycaster->sideDistY = (player->posY - player->mapY) * raycaster->deltaDistY;
    }
    else
    {
        raycaster->stepY = 1;
        raycaster->sideDistY = (player->mapY + 1.0 - player->posY) * raycaster->deltaDistY;
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
        {
            raycaster->hit = 1;
        }
    }

    if (raycaster->side == 0)
    {
        raycaster->perpWallDist = (player->mapX - player->posX + (1 - raycaster->stepX) / 2) / raycaster->rayDirX;
    }
    else
    {
        raycaster->perpWallDist = (player->mapY - player->posY + (1 - raycaster->stepY) / 2) / raycaster->rayDirY;
    }

    raycaster->lineHeight = (int)(SCREEN_HEIGHT / raycaster->perpWallDist);

    raycaster->drawStart = -raycaster->lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (raycaster->drawStart < 0)
    {
        raycaster->drawStart = 0;
    }

    raycaster->drawEnd = raycaster->lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (raycaster->drawEnd >= SCREEN_HEIGHT)
    {
        raycaster->drawEnd = SCREEN_HEIGHT - 1;
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

    // Floor and ceiling rendering
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
            // Cell coordinates
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            // Texture coordinates
            int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
            int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

            floorX += floorStepX;
            floorY += floorStepY;

            // Choose texture and draw the pixel
            int floorTexture = 3;
            int ceilingTexture = 6;

            // Floor
            Uint32 color = gw->gt->texture[floorTexture][texWidth * ty + tx];
            color = (color >> 1) & 8355711; // Make a bit darker
            gw->buffer[y][x] = color;

            // Ceiling (symmetrical)
            color = gw->gt->texture[ceilingTexture][texWidth * ty + tx];
            color = (color >> 1) & 8355711; // Make a bit darker
            gw->buffer[SCREEN_HEIGHT - y - 1][x] = color;
        }
    }

    // Wall rendering
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        set_horizontal_raycaster_values(&raycaster, player, x);
        cast_rays(&raycaster, player);
        int texNum = raycaster.map->map[player->mapX][player->mapY] - 1; // 1 subtracted from it so that texture 0 can be used!

        // Calculate value of wallX
        double wallX; // Where exactly the wall was hit
        if (raycaster.side == 0)
        {
            wallX = player->posY + raycaster.perpWallDist * raycaster.rayDirY;
        }
        else
        {
            wallX = player->posX + raycaster.perpWallDist * raycaster.rayDirX;
        }
        wallX -= floor((wallX));

        // X coordinate on the texture
        int texX = (int)(wallX * (double)(texWidth));
        if (raycaster.side == 0 && raycaster.rayDirX > 0)
        {
            texX = texWidth - texX - 1;
        }
        if (raycaster.side == 1 && raycaster.rayDirY < 0)
        {
            texX = texWidth - texX - 1;
        }

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * texHeight / raycaster.lineHeight;
        // Starting texture coordinate
        double texPos = (raycaster.drawStart - SCREEN_HEIGHT / 2 + raycaster.lineHeight / 2) * step;
        for (int y = raycaster.drawStart; y < raycaster.drawEnd; y++)
        {
            // Cast the texture coordinate to integer and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            Uint32 color = gw->gt->texture[texNum][texWidth * texY + texX];
            // Make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if (raycaster.side == 1)
            {
                color = (color >> 1) & 8355711;
            }
            gw->buffer[y][x] = color;
        }

		gw->Zbuffer[x] = raycaster.perpWallDist;
    }
}
