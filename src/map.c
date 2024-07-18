#include "../headers/main.h"
#include <stdlib.h>

/**
 * draw_minimap - draws a mini-map on the screen.
 *
 * @gw: game window.
 * @player: player.
 * @map: the map.
 */
void draw_minimap(GameWindow_t *gw, Player_t *player, Map_t *map)
{
	Uint32 wall_color = rgb(200, 200, 200), player_color = rgb(0, 0, 0);
	Uint32 direction_color = rgb(0, 255, 0);
	int x, y, player_minimap_x, player_minimap_y, line_length, line_thickness,
		dx, dy;

	for (int y = 0; y < map->rows; y++)
		for (int x = 0; x < map->cols; x++)
			if (map->map[x][y] > 0)
				for (int i = 0; i < MINIMAP_SCALE; i++)
					for (int j = 0; j < MINIMAP_SCALE; j++)
						gw->buffer[
							MINIMAP_Y_OFFSET + y * MINIMAP_SCALE + i][
							MINIMAP_X_OFFSET + x * MINIMAP_SCALE +
							j] = wall_color;

	player_minimap_x = MINIMAP_X_OFFSET + player->posX * MINIMAP_SCALE;
	player_minimap_y = MINIMAP_Y_OFFSET + player->posY * MINIMAP_SCALE;
	for (int i = -(MINIMAP_SCALE / 2); i < MINIMAP_SCALE / 2; i++)
		for (int j = -(MINIMAP_SCALE / 2); j < MINIMAP_SCALE / 2; j++)
			gw->buffer[player_minimap_y + i][
				player_minimap_x + j] = player_color;

	line_length = 2 * MINIMAP_SCALE, line_thickness = 3;
	for (int t = -line_thickness; t <= line_thickness; t++)
	{
		dx = t * player->dirX;
		dy = t * player->dirY;
		for (int l = 0; l < line_length; l++)
		{
			x = player_minimap_x + l * player->dirX + dx;
			y = player_minimap_y + l * player->dirY + dy;
			if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
				gw->buffer[y][x] = direction_color;
		}
	}
}


/**
 * read_map_items - read map from a given file *file.
 *
 * @file: file to be readed.
 * @map: where to store the file.
 */
void read_map_items(FILE *file, Map_t *map)
{
	int current_col = 0;
	char ch, c;

	while ((ch = fgetc(file)) != EOF)
		switch (ch)
		{
			case ' ':
			case '\n':
			case '\r':
			case '{':
				continue;
			case '}':
			{
				c = fgetc(file);
				if (c == ',')
				{
					if (current_col)
						map->cols = current_col;
					map->rows += 1, current_col = 0;
				}
				else
				ungetc(c, file);
			}
			break;
			default:
			{
				if (isdigit(ch))
				{
					ungetc(ch, file);
					fscanf(file, "%d", &map->map[map->rows][current_col]);
					current_col++;
				}
			}
			break;
		}
	map->rows += 1;
}

/**
 * read_map - reads a map from a file.
 *
 * @map: where to store the map
 * @file_path: the filepath to store the map.
 *
 * Return: the array of map or null.
 */
int **read_map(Map_t *map, const char *file_path)
{
	FILE *file = fopen(file_path, "r");
	int max_rows = 100, max_cols = 100;

	if (file == NULL)
	{
		perror("Error opening file");
		return (NULL);
	}

	map->map = (int **)malloc(max_rows * sizeof(int *));
	for (int i = 0; i < max_rows; i++)
		map->map[i] = (int *)malloc(max_cols * sizeof(int));

	read_map_items(file, map);
	for (int i = map->rows; i < max_rows; i++)
		free(map->map[i]);

	fclose(file);
	return (map->map);
}

/**
 * free_map - function to free the map.
 *
 * @map: the map to be freed.
 */
void free_map(Map_t *map)
{
	if (!map || !(map->map))
		return;

	for (int i = 0; i < map->rows; i++)
		free(map->map[i]);

	free(map->map);
}

/**
 * parse_game_map - parses a game map from argc, argv[1].
 *
 * @argc: argument count.
 * @argv: the argument vector.
 * @map: the map to be stored.
 */
void parse_game_map(int argc, char *argv[], Map_t *map)
{
	if (argc != 2)
    {
		perror("Usage maze <path to the file> ");
        exit(EXIT_FAILURE);
    }
	read_map(map, argv[1]);
}
