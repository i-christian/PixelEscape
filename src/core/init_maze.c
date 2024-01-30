#include "../../inc/main.h"
#include <stdio.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL.h>


/**
* init_maze - initialise the maze
* @gInstance: param
* Return: 0 for success or 1 for for failure
*/

int init_maze(SDL_Instance *gInstance)
{
	int SCREEN_WIDTH = 1280;
	int SCREEN_HEIGTH = 720;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialise SDL: %s\n", SDL_GetError());
		return (1);
	}

	/*Create a new window instance*/
	gInstance->window = SDL_CreateWindow(
									  "PixelEscape: 3D RaycastingMaze Adventure",
									  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
									  SCREEN_WIDTH, SCREEN_HEIGTH, 0 |
									  SDL_WINDOW_RESIZABLE);
	if (gInstance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return (1);
	}

	/*Create a new renderer instance linked to the window*/
	gInstance->renderer = SDL_CreateRenderer(gInstance->window, -1,
										  SDL_RENDERER_ACCELERATED |
										  SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (gInstance->renderer == NULL)
	{
		SDL_DestroyWindow(gInstance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return (1);
	}

	return (0);
}
