#include "../inc/main.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>

/**
 * cleanup - Maze entry point
 * @gInstance: param
 * Return: nothing at all
 */
void cleanup(SDL_Instance *gInstance)
{
	SDL_DestroyRenderer(gInstance->renderer);
	SDL_DestroyWindow(gInstance->window);
	SDL_Quit();
}

/**
 * main - Maze entry point
 * Return: 0 for success or 1 for error
 */

int main(void)
{
	SDL_Instance gInstance;
	bool quit = false;

	if (init_maze(&gInstance) != 0)
	{
		fprintf(stderr, "Failed to initialize maze: %s\n", SDL_GetError());
		return (1);
	}
	/*Game loop */
	while (quit == false)
	{
		quit = poll_event(quit);
			SDL_RenderClear(gInstance.renderer);
		/*Raycasting algorithm */
		renderWalls(&gInstance);
		SDL_RenderPresent(gInstance.renderer);
	}

	/*Clean up the game*/
	cleanup(&gInstance);
	return (0);
}
