#include "../../inc/main.h"

/**
 * runGame - game loop
 * Return: nothing
 */

void runGame(gameData *gameData)
{
    long gameTicks = 0;
    long time;

    do {
        time = SDL_GetTicks();

        /* Handle SDL key events */
        handleEvents(gameData);

        /* Update the player */
        updatePlayer();

        /* Update the raycaster */
        updateRaycaster(gameData);

        /* Render a frame */
        render(gameData);

        /* Fixed delay before next frame */
        SDL_Delay(10);

        /* Print FPS every 500 frames */
        if(!(gameTicks++ % 500))
            fprintf(stderr, "FPS: %.2f\n", 1000.0f / (float)(SDL_GetTicks() - time));
    } while(gameData->gameIsRunning);
}
