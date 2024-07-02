#include "../headers/main.h"
#include <iostream>

/**
 * render - displays renders a given buffer to a specific renderer.
 *
 * @renderer: renderer to use.
 * @texture: the texture to be rendered.
 */
void render(SDL_Renderer *renderer, SDL_Texture *texture)
{
	SDL_UpdateTexture(texture, NULL, screen.buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(screen.renderer);
	SDL_RenderCopy(screen.renderer, texture, NULL, NULL);
	drawMiniMap();
	SDL_RenderPresent(screen.renderer);
}


/**
 * destroy_game - deallocates all the game resources.
 */
void destroy_game()
{
	if (screen.texture)
		SDL_DestroyTexture(screen.texture);
	if (screen.renderer)
		SDL_DestroyRenderer(screen.renderer);
	if (screen.window)
		SDL_DestroyWindow(screen.window);

	SDL_Quit();
}


/**
 * init_game - function that will initialize all the game resources.
 */
void init_game()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	screen.window = SDL_CreateWindow(
		"Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN
		);

	if (screen.window == nullptr)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	screen.renderer = SDL_CreateRenderer(
		screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);
	if (screen.renderer == nullptr)
	{
		SDL_DestroyWindow(screen.window);
		std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	screen.texture = SDL_CreateTexture(screen.renderer, SDL_PIXELFORMAT_ARGB8888,
				SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (screen.texture == nullptr)
	{
		std::cerr << "No texture created\n";
		destroy_game();
		exit(1);
	}
}
