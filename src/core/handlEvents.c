#include "../../inc/main.h"

/**
 * handleEvents - Event handler function
 * @gameData: Pointer to game data struct
 *
 * This function handles SDL events such as key presses and window events.
 * It updates the game state based on user input.
 *
 * Return: Nothing
 */
void handleEvents(gameData *gameData) {
    SDL_Event event;
    char keyIsDown;

    while(SDL_PollEvent(&event)) {
        keyIsDown = (event.type == SDL_KEYDOWN);
        switch(event.type) {
            case SDL_KEYUP:
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        movingForward = keyIsDown;
                        break;
                    case SDLK_DOWN:
                        movingBack = keyIsDown;
                        break;
                    case SDLK_LEFT:
                        turningLeft = keyIsDown;
                        break;
                    case SDLK_RIGHT:
                        turningRight = keyIsDown;
                        break;
                    case SDLK_LSHIFT:
                    case SDLK_RSHIFT:
                        playerIsRunning = keyIsDown;
                        break;
                    case SDLK_ESCAPE:
                        gameData->gameIsRunning = FALSE;
                        break;
                    case SDLK_t:
                        if(keyIsDown) gameData->textureMode = (gameData->textureMode + 1) % 2;
                        break;
                    case SDLK_m:
                        if(keyIsDown)
                            gameData->showMap = !(gameData->showMap);
                        break;
                    case SDLK_d:
                        if(keyIsDown) gameData->distortion = !gameData->distortion;
                        break;

                    case SDLK_f:
                        if(keyIsDown) {
                            /* Toggle fullscreen mode */
                            Uint32 fullscreenFlag = SDL_GetWindowFlags(gInstance.window) & SDL_WINDOW_FULLSCREEN;
                            SDL_SetWindowFullscreen(gInstance.window, fullscreenFlag ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP);
                        }
                        break;
                    case SDLK_r:
                        if(keyIsDown) gameData->slowRenderMode = !gameData->slowRenderMode;
                        break;
                    case SDLK_c:
                        if(keyIsDown) gameData->rayCastMode = (gameData->rayCastMode + 1) % 3;
                        break;
                    case SDLK_LEFTBRACKET:
                        if(keyIsDown && distFromViewplane - 20.0f > 100.0f) distFromViewplane -= 20.0f;
                        break;
                    case SDLK_RIGHTBRACKET:
                        if(keyIsDown) distFromViewplane += 20.0f;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_QUIT:
                gameData->gameIsRunning = FALSE;
                break;
            default:
                break;
        }
    }
}
