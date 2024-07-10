#include "../headers/main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

// Function to load texture from image
bool get_texture_from_image(Uint32 **texture, unsigned long *tw, unsigned long *th, const char *filename) {
    SDL_Surface *surface = IMG_Load(filename);
    if (!surface) {
        fprintf(stderr, "Failed to load image %s: %s\n", filename, IMG_GetError());
        return false;
    }

    // Convert the surface to a known pixel format
    SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
    SDL_FreeSurface(surface); // Free the original surface

    if (!formattedSurface) {
        fprintf(stderr, "Failed to convert surface %s: %s\n", filename, SDL_GetError());
        return false;
    }

    // Get the width and height of the image
    *tw = formattedSurface->w;
    *th = formattedSurface->h;

    // Allocate memory for the texture data
    *texture = (Uint32 *)malloc(sizeof(Uint32) * (*tw) * (*th));
    if (!*texture) {
        fprintf(stderr, "Failed to allocate memory for texture\n");
        SDL_FreeSurface(formattedSurface);
        return false;
    }

    // Copy pixel data from surface to texture
    Uint32 *pixels = (Uint32 *)formattedSurface->pixels;
    for (unsigned long i = 0; i < (*tw) * (*th); ++i) {
        (*texture)[i] = pixels[i];
    }

    // Free the formatted surface
    SDL_FreeSurface(formattedSurface);
    return true;
}

// Function to allocate textures
void allocate_textures(GameTexture_t *gt) {
    bool error = false;
    unsigned long tw, th;
    const char *images[TEXTURE_SIZE] = {
        "pics/wood.png", "pics/eagle.png",
        "pics/redbrick.png", "pics/purplestone.png",
        "pics/greystone.png", "pics/bluestone.png",
        "pics/mossy.png", "pics/colorstone.png"
    };

    if (!gt) return;

    for (int i = 0; i < TEXTURE_SIZE; i++) {
        if (images[i] != NULL && images[i][0]) {
            if (!get_texture_from_image(&(gt->texture[i]), &tw, &th, images[i])) {
                error = true;
            }
        }
        if (gt->texture[i]) {
            printf("Loaded texture at %d: %s\n", i, images[i]);
        } else {
            printf("Failed to load texture at %d: %s\n", i, images[i]);
        }
    }

    if (error) {
        fprintf(stderr, "Unable to get some textures\n");
        exit(1);
    }
}

// Function to free textures
void free_textures(GameTexture_t *gt) {
    if (gt) {
        for (int i = 0; i < TEXTURE_SIZE; i++) {
            if (gt->texture[i]) {
                free(gt->texture[i]);
                gt->texture[i] = NULL;
            }
        }
    }
}