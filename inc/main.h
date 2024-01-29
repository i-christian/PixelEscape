#ifndef _MAIN_
#define _MAIN_

#include <SDL2/SDL.h>

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
void close(void);
int poll_event(void);

#endif /* !_MAIN_ */
