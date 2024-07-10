#include "../headers/main.h"

int WorldMap[MAP_HEIGHT][MAP_WIDTH] = {
		{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
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
	};

/**
 * draw_minimap - draws a mini-map on the screen.
 *
 * @gw: game window.
 * @player: player.
 */
void draw_minimap(GameWindow_t *gw, Player_t *player, Map_t *map)
{
	Uint32 wall_color = rgb(200, 200, 200);
	Uint32 player_color = rgb(255, 0, 0);
	
	for (int y = 0; y < map->rows; y++)
	{
		for (int x = 0; x < map->cols; x++)
		{
			if (map->map[x][y] > 0)
			{
				for (int i = 0; i < MINIMAP_SCALE; i++)
				{
					for (int j = 0; j < MINIMAP_SCALE; j++)
						gw->buffer[MINIMAP_Y_OFFSET + y * MINIMAP_SCALE + i
							][MINIMAP_X_OFFSET + x * MINIMAP_SCALE + j] = wall_color;
				}
			}
		}
	}

	/* Draw the player on the mini-map */
	int player_minimap_x = MINIMAP_X_OFFSET + player->posX * MINIMAP_SCALE;
	int player_minimap_y = MINIMAP_Y_OFFSET + player->posY * MINIMAP_SCALE;

	for (int i = -(MINIMAP_SCALE / 2); i < MINIMAP_SCALE / 2; i++)
	{
		for (int j = -(MINIMAP_SCALE / 2); j < MINIMAP_SCALE / 2; j++)
			gw->buffer[player_minimap_y + i][
				player_minimap_x + j] = player_color;
	}
}

void read_map_items(FILE *file, Map_t *map)
{
	int current_col = 0;
	char ch;

	while ((ch = fgetc(file)) != EOF) {
		putchar(ch);
		switch (ch)
		{
			case ' ':
			case '\n':
			case '\r':
			case '{':
				continue;
			case '}':
				{
					char c = fgetc(file);
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
	}

	map->rows += 1;
}

int** read_map(Map_t *map, const char *file_path) {
	FILE *file = fopen(file_path, "r");
	int max_rows = 100, max_cols = 100;

	if (file == NULL) {
		perror("Error opening file");
		return NULL;
	}

	map->map = (int **)malloc(max_rows * sizeof(int *));
	for (int i = 0; i < max_rows; i++) {
		map->map[i] = (int *)malloc(max_cols * sizeof(int));
	}

	read_map_items(file, map);

	for (int i = map->rows; i < max_rows; i++)
		free(map->map[i]);

	fclose(file);
	return map->map;
}

void free_map(Map_t *map) {
	if (!map || !(map->map))
		return;

	for (int i = 0; i < map->rows; i++) {
		free(map->map[i]);
	}

	free(map->map);
}

void parse_game_map(int argc, char *argv[], Map_t *map)
{
	if (argc != 2)
		perror("Usage maze <path to the file>\n");
	else
		read_map(map, argv[1]);
}