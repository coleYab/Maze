#ifndef __GAME_STRUCTS_H
#define __GAME_STRUCTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_image.h>

#define GAME_START         (0)
#define GAME_PLAYING       (1)
#define GAME_END           (2)
#define TEXTURE_SIZE       (10)
#define TEXTURE_WIDTH      (64)
#define TEXTURE_HEIGHT     (64)
#define SCREEN_WIDTH       (1200)
#define SCREEN_HEIGHT      (720)
#define MOVING_SPEED       (0.2)
#define ROTATION_SPEED     (0.2)
#define MAP_WIDTH          (24)
#define MAP_HEIGHT         (24)
#define MINIMAP_SCALE      (10)
#define MINIMAP_X_OFFSET   (10)
#define MINIMAP_Y_OFFSET   (10)

/**
 * struct Map - represents a game map.
 * @map: a 2D array representing the map layout.
 * @rows: the number of rows in the map.
 * @cols: the number of columns in the map.
 */
typedef struct Map
{
	int **map;
	int rows;
	int cols;
} Map_t;

/**
 * struct Player - represents the player in the game.
 *
 * @posX: player's position on the X axis.
 * @posY: player's position on the Y axis.
 * @dirX: player's direction vector X.
 * @dirY: player's direction vector Y.
 * @planeX: the camera plane vector X.
 * @planeY: the camera plane vector Y.
 * @cameraX: the camera X coordinate.
 * @cameraY: the camera Y coordinate.
 * @mapX: player's map grid X coordinate.
 * @mapY: player's map grid Y coordinate.
 */
typedef struct Player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double cameraX;
	double cameraY;
	int mapX;
	int mapY;
} Player_t;

/**
 * struct Raycaster - represents the ray casting logic.
 *
 * @rayDirX: direction of the ray on the X axis.
 * @rayDirY: direction of the ray on the Y axis.
 * @sideDistX: distance to the next side on the X axis.
 * @sideDistY: distance to the next side on the Y axis.
 * @deltaDistX: distance from one X-side to the next X-side.
 * @deltaDistY: distance from one Y-side to the next Y-side.
 * @perpWallDist: perpendicular distance from the wall.
 * @stepX: step direction on the X axis.
 * @stepY: step direction on the Y axis.
 * @hit: indicates if a wall has been hit.
 * @side: indicates if the hit is on an X or Y side.
 * @lineHeight: height of the line to draw on screen.
 * @drawStart: start coordinate of the line to draw.
 * @drawEnd: end coordinate of the line to draw.
 * @map: pointer to the Map struct.
 */
typedef struct Raycaster
{
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	Map_t *map;
} RayCaster_t;

/**
 * struct GameTexture - represents game textures.
 *
 * @texture: an array of pointers to texture data.
 */
typedef struct GameTexture
{
	Uint32 * texture[TEXTURE_SIZE];
} GameTexture_t;

/**
 * struct GameWindow - represents the game window and rendering context.
 *
 * @window: pointer to the SDL window.
 * @renderer: pointer to the SDL renderer.
 * @instantiated: indicates if the window and renderer are instantiated.
 * @buffer: pixel buffer for the screen.
 * @gt: pointer to the GameTexture struct.
 * @display_map: flag to display the mini-map.
 * @Zbuffer: array for storing Z-buffer values.
 * @game_state: current state of the game (
 *			e.g., GAME_START, GAME_PLAYING, GAME_END).
 */
typedef struct GameWindow
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool instantiated;
	Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	GameTexture_t *gt;
	bool display_map;
	double Zbuffer[SCREEN_WIDTH];
	int game_state;
} GameWindow_t;

#endif
