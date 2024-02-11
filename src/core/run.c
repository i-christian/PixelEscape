#include "../../inc/main.h"

/**
 * runGame - Game loop controlling the main flow of the game.
 *
 * @gameData: Pointer to the game data struct.
 * @audioData: Pointer to the audio data struct.
 *
 * Description: This function runs the game loop, handling events, updating player position,
 * updating the raycaster, rendering frames, and playing background music.
 * It also includes a fixed delay between frames and prints FPS every 500 frames.
 *
 * Return: void
 */
void runGame(gameData *gameData, AudioData *audioData)
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
		playBackgroundMusic(audioData);

        /* Fixed delay before next frame */
        SDL_Delay(10);

        /* Print FPS every 500 frames */
        if(!(gameTicks++ % 500))
            fprintf(stderr, "FPS: %.2f\n", 1000.0f / (float)(SDL_GetTicks() - time));
    } while(gameData->gameIsRunning);
}
