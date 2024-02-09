#ifndef RENDERER_H
#define RENDERER_H

#include "graphics.h"
#include "linear_algebra.h"
#include "game_data.h"
#include <stdlib.h>

/* Macros */
#define XY_TO_SCREEN_INDEX(X, Y)   (((Y) * WINDOW_WIDTH) + (X))
#define XY_TO_TEXTURE_INDEX(X, Y)   (((Y) * TEXTURE_SIZE) + (X))
#define DARKEN_COLOR(C)     ((((C) >> 1) & 0x7F7F7F7F) | 0xFF000000)

/**
 *  enum RayType - enum representing rays
 *  @HORIZONTAL_RAY: member1
 *  @VERTICAL_RAY: member2
 */
typedef enum RayType
{
  HORIZONTAL_RAY,
  VERTICAL_RAY
} RayType;

/* Functions */
float calculateDrawHeight(float rayLength);
void drawTexturedStrip(gameData *gameData, int x, float wallYStart, float length, int textureX, Uint32 *texture, char darken);
void drawUntexturedStrip(gameData *gameData, int x, float wallYStart, float length, Uint32 ABGRColor, char darken);
int getTextureColumnNumberForRay(Vector3f *ray, RayType rtype);
float getUndistortedRayLength(Vector3f *ray);
void renderProjectedScene(gameData *gameData);

#endif /* RENDERER_H */
