#include <SDL2/SDL_events.h>
#include <stdbool.h>

/**
 * poll_event - a function that handles events un the game
 * @quit: param
 * Return: true for success or false for failure
 */

bool poll_event(bool quit)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			quit = true;
	}
	return (quit);
}
