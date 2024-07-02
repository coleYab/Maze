#include "../headers/main.h"

bool is_exit_event(SDL_Event *event)
{
	if (event)
	{
		while (SDL_PollEvent(event))
		{
			if (event->type == SDL_QUIT)
				return false;
			return true;
		}
	}
	return true;
}