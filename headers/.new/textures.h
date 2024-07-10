#ifndef __TEXTURES__
#define __TEXTURES__

#define TEXTURE_SIZE (10)
#define texWidth (64)
#define	texHeight (64)

/* texture related files */
typedef struct {
    Uint32 *texture[TEXTURE_SIZE];
} GameTexture_t;

void allocate_textures(GameTexture_t *);
void free_textures(GameTexture_t *);

#endif