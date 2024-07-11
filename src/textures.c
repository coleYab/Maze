#include "../headers/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * get_texture_from_image - gets texture form the image at filename.
 *
 * @texture: the texture ** to be updated.
 * @tw: texture width.
 * @th: texture height.
 * @filename: the filename for the item.
 *
 * Return: Allocation result.
 */
bool get_texture_from_image(Uint32 **texture,
	unsigned long *tw, unsigned long *th, const char *filename)
{
	Uint32 *pixels;
	SDL_Surface *formattedSurface, *surface;

	surface = IMG_Load(filename);
	if (!surface)
	{
		fprintf(stderr, "Failed to load image %s: %s\n", filename, IMG_GetError());
		return (false);
	}

	formattedSurface = SDL_ConvertSurfaceFormat(
		surface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(surface);
	if (!formattedSurface)
	{
		fprintf(stderr, "Failed to convert surface %s: %s\n",
			filename, SDL_GetError());
		return (false);
	}

	*tw = formattedSurface->w;
	*th = formattedSurface->h;
	*texture = (Uint32 *)malloc(sizeof(Uint32) * (*tw) * (*th));
	if (!*texture)
	{
		fprintf(stderr, "Failed to allocate memory for texture\n");
		SDL_FreeSurface(formattedSurface);
		return (false);
	}

	pixels = (Uint32 *)formattedSurface->pixels;
	for (unsigned long i = 0; i < (*tw) * (*th); ++i)
		(*texture)[i] = pixels[i];

	SDL_FreeSurface(formattedSurface);
	return (true);
}

/**
 * allocate_textures - allocates the textures from the listed images.
 *
 * @gt: game texture to be allocated.
 */
void allocate_textures(GameTexture_t *gt)
{
	bool error = false;
	unsigned long tw, th;
	const char *images[TEXTURE_SIZE] = {
		"pics/eagle.png", "pics/redbrick.png",
		"pics/purplestone.png", "pics/greystone.png",
		"pics/bluestone.png", "pics/mossy.png",
		"pics/wood.png", "pics/colorstone.png"
	};

	if (!gt)
		return;

	for (int i = 0; i < TEXTURE_SIZE; i++)
	{
		if (images[i] != NULL && images[i][0])
			if (!get_texture_from_image(&(gt->texture[i]), &tw, &th, images[i]))
				error = true;
	}

	if (error)
	{
		fprintf(stderr, "Unable to get some textures\n");
		exit(1);
	}
}

/**
 * free_textures - deletes all the textures allocated.
 *
 * @gt: game texture to delete.
 */
void free_textures(GameTexture_t *gt)
{
	if (gt)
	{
		for (int i = 0; i < TEXTURE_SIZE; i++)
		{
			if (gt->texture[i])
			{
				free(gt->texture[i]);
				gt->texture[i] = NULL;
			}
		}
	}
}
