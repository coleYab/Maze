#include "../headers/main.h"

/**
 * is_exit_event - function to check if user want to exit.
 *
 * @event: the event to check.
 */
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