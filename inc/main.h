#ifndef _MAIN_
#define _MAIN_

#include <SDL2/SDL.h>
#include <stdbool.h>
/**
 * struct SDL_Instance - an instance of SDL
 * @window: a pointer to SDL_Window
 * @renderer: a pointer to SDL_Renderer
 */

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/* Function definitions */
int init_maze(SDL_Instance *);
bool poll_event(bool quit);
void renderWalls(SDL_Instance *);

#endif /* !_MAIN_ */
