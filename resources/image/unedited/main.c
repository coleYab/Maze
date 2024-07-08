#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int** read_map(const char *file_path, int *rows, int *cols) {
	FILE *file = fopen(file_path, "r");
	if (file == NULL) {
		perror("Error opening file");
		return NULL;
	}

	// Assuming the maximum possible dimensions of the map are known or set
	int max_rows = 100, max_cols = 100;
	int **map = (int **)malloc(max_rows * sizeof(int *));
	for (int i = 0; i < max_rows; i++) {
		map[i] = (int *)malloc(max_cols * sizeof(int));
	}

	char ch;
	*rows = 0;
	*cols = 0;
	int current_row = 0, current_col = 0;
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
							*cols = current_col;
						*rows += 1, current_col = 0;
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
						fscanf(file, "%d", &map[*rows][current_col]);
						current_col++;
					}
				}
				break;
		}
	}

	*rows += 1;
	
	for (int i = *rows; i < max_rows; i++)
		free(map[i]);
	
	fclose(file);
	return map;
}

void free_map(int **map, int rows) {
	for (int i = 0; i < rows; i++) {
		free(map[i]);
	}
	free(map);
}
