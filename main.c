#include "inc/main.h"


/**
 * main - Maze entry point
 * Return: 0 for success or 1 for error
 */

int main(void)
{
	SDL_Instance gInstance;

	if (init_maze(&gInstance) < 0)
		return (1);
	return (0);
}
