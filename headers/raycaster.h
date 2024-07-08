#ifndef __RAYCASTER_TOOLS
#define __RAYCASTER_TOOLS

#include "map.h"

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


#endif