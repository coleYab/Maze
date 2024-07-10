#ifndef __GAME_STRUCTS_H
#define __GAME_STRUCTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_image.h>

#define TEXTURE_SIZE (10)
#define texWidth (64)
#define	texHeight (64)
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
#define MOVING_SPEED (0.2)
#define ROTATION_SPEED (0.2)
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define MINIMAP_SCALE 10  // Scale factor for the mini-map
#define MINIMAP_X_OFFSET 10  // X position of the mini-map
#define MINIMAP_Y_OFFSET 10  // Y position of the mini-map

typedef struct {
    int **map;
    int rows;
    int cols;
} Map_t;

extern int WorldMap[MAP_HEIGHT][MAP_WIDTH];

typedef struct
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

typedef struct {
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


typedef struct {
    Uint32 *texture[TEXTURE_SIZE];
} GameTexture_t;

typedef struct GameWindow
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool instantiated;
    Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    GameTexture_t *gt;
    bool display_map;
    double Zbuffer[SCREEN_WIDTH];
} GameWindow_t;

typedef struct {
    GameWindow_t *gw;
    Map_t *map;
    Player_t *player;
    GameTexture_t *texture;
} Game_t;

#endif
