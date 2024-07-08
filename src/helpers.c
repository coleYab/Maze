#include "../headers/game.h"

/**
 * reset_game_buffer - sets all the game buffers to 0.
 *
 * @gw: the game window.
 */
void reset_game_buffer(GameWindow_t *gw)
{
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH; ++x)
			gw->buffer[y][x] = 0;
	}
}

/**
 * draw_vertical_line - function to draw vertical line.
 *
 * @gw: game window.
 * @x: the colmun.
 * @start: the starting row.
 * @end: the ending row.
 * @color: specific color to draw.
 */
void draw_vertical_line(
	GameWindow_t *gw, int x, int start, int end, Uint32 color)
{
	for (int y = start; y < end; y++)
	{
		gw->buffer[y][x] = color;
	}
}

/**
 * rgb - function to turn the rgb values to their color representation.
 *
 * @r: the red value.
 * @g: the green value.
 * @b: the blue value.
 *
 * Return: the specific color.
 */
Uint32 rgb(Uint8 r, Uint8 g, Uint8 b)
{
	return ((r << 16) | (g << 8) | b);
}


/**
 * get_color_from_map - returns the specific color in a map.
 *
 * @mapX: the X coordinate.
 * @mapY: the y coordinate.
 *
 * Return: the color at that stage.
 */
Uint32 get_color_from_map(int **map, int mapX, int mapY)
{
	Uint32 color;

	switch (map[mapX][mapY])
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

	return (color);
}
