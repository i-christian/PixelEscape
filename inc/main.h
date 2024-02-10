#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "audio.h"
#include "config.h"
#include "raycaster.h"
#include "renderer.h"
#include "player.h"
#include "map.h"
#include "graphics.h"
#include "game_data.h"

/* Function definitions */
void render(gameData *gameData);
void handleEvents(gameData *gameData);
void runGame(gameData *gameData, AudioData *audioData);
void initAudio(AudioData *audioData);

#endif /* _MAIN_ */
