#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "config.h"

/**
 * struct GameData - Keeps programme grobals
 * @screenBuffer: first member
 * @redXorTexture: second member
 * @greenXorTexture: Third member
 * @blueXorTexture: Third member
 * @grayXorTexture: Fourth member
 * @TEXTURES: Fifth member
 * @COLORS: Sixth member
 * @gameIsRunning: Seventh member
 * @showMap: eight member
 * @distortion: ninth member
 * @slowRenderMode: tenth member
 * @rayCastMode: eleventh member
 * @textureMode: last member
 */

typedef struct GameData
{
  Uint32 *screenBuffer;
  Uint32 *redXorTexture;
  Uint32 *greenXorTexture;
  Uint32 *blueXorTexture;
  Uint32 *grayXorTexture;
  Uint32 *TEXTURES[4];
  Uint32 COLORS[4];
  char gameIsRunning;
  char showMap;
  char distortion;
  char slowRenderMode;
  char rayCastMode;
  char textureMode;
} gameData;

#endif /* GAME_DATA_H */
