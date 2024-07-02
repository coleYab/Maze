#ifndef ___MAZE_G_
#define ___MAZE_G_

#include <SDL2/SDL.h>

#define mapWidth 24
#define mapHeight 24
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
#define texWidth 64
#define texHeight 64
#define miniMapScale 10

typedef struct Screen
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
} Screen_t;

typedef struct {
	int worldMap[mapWidth][mapHeight];
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX ;
	double planeY;
} World_t;

extern World_t world;
extern Screen_t screen;

#define moveSpeed 0.3
#define rotSpeed 0.2


/* Game event related functions 	*/
bool is_exit_event(SDL_Event *event);
void drawMiniMap();
Uint32 get_color_from_map(int mapX, int mapY);
void reset_game_buffer();
void drawVerticalLine(int x, int start, int end, Uint32 color);
void move_player();
void render(SDL_Renderer *, SDL_Texture *);
void init_game();
void game_loop();
void destroy_game();
void drawMiniMap();
void draw_world();


#endif /* ___MAZE_G_*/