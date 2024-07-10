#ifndef __PLAYER_
#define __PLAYER_

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

#define MOVING_SPEED (0.2)
#define ROTATION_SPEED (0.2)

void move_player(Player_t *);

#endif
