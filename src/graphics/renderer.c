#include "../../inc/main.h"

/**
 * Calculate the draw height of a pixel column for a given
 * ray length.
 *
 * @rayLength: The ray length to use.
 *
 * Returns: The pixel height of a vertical column to draw.
 */
float calculateDrawHeight(float rayLength) {
    return distFromViewplane * WALL_SIZE / rayLength;
}


/**
 * drawUntexturedStrip - Draw untextured wall strips.
 *
 * @gameData: Pointer to the game data structure.
 * @x: The x-coordinate of the strip.
 * @wallYStart: The starting y-coordinate of the strip.
 * @length: The length of the strip.
 * @ABGRColor: The color of the strip.
 * @darken: Non-zero if the strip should be darkened, zero otherwise.
 * Return: nothing
*/
void drawUntexturedStrip(gameData *gameData, int x, float wallYStart, float length, Uint32 ABGRColor, char darken) {
    int y;

    if(wallYStart < 0)
        wallYStart = 0;

    for(y = 0; y < WINDOW_HEIGHT; y++) {
        if(y < wallYStart) {
            gameData->screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = CEILING_COLOR;
        } else if(y > (wallYStart + length)) {
            gameData->screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = FLOOR_COLOR;
        } else {
            gameData->screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = (darken) ? ABGRColor : DARKEN_COLOR(ABGRColor);
        }
    }
}


/**
 * drawTexturedStrip - Draw a textured pixel column on the screen.
 *
 * @gameData: Pointer to the game data structure.
 * @x: The x-coordinate of the column.
 * @wallYStart: The starting y-coordinate of the column.
 * @length: The length of the column.
 * @textureX: The texture column number to use for the strip.
 * @texture: The texture to use.
 * @darken: Non-zero if the strip should be darkened, zero otherwise.
 * Return: nothing
 */
void drawTexturedStrip(gameData *gameData, int x, float wallYStart, float length, int textureX, Uint32* texture, char darken) {
    int y;
    float d, ty;
    Uint32 color;

    if(wallYStart < 0)
        wallYStart = 0;

    for(y = 0; y < WINDOW_HEIGHT; y++) {
        d = y - (WINDOW_HEIGHT / 2.0f) + length / 2.0f;
        ty = d * (float)(TEXTURE_SIZE-EPS) / length;

        if(y < wallYStart) {
            gameData->screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = CEILING_COLOR;
        } else if(y > (wallYStart + length)) {
            gameData->screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = FLOOR_COLOR;
        } else {
            color = texture[XY_TO_TEXTURE_INDEX(textureX, (int)ty)];
            if(darken) color = DARKEN_COLOR(color);

            gameData->screenBuffer[XY_TO_SCREEN_INDEX(x, y)] = color;
        }
    }

}


/**
 * getTextureColumnNumberForRay - Find the texture column number to use for a given ray.
 *
 * @ray: The ray to use.
 * @rtype: The type of ray intersection (see above definition of RayType).
 *
 * Returns: The texture column number to use.
 */
int getTextureColumnNumberForRay(Vector3f* ray, RayType rtype) {
    Vector3f rayHitPos = vectorAdd(&playerPos, ray);
    if(rtype == HORIZONTAL_RAY) {
        if(ray->y < 0)
            return (int)rayHitPos.x % TEXTURE_SIZE;
        else
            return TEXTURE_SIZE - 1 - ((int)rayHitPos.x % TEXTURE_SIZE);
    } else {
        if(ray->x > 0)
            return (int)rayHitPos.y % TEXTURE_SIZE;
        else
            return TEXTURE_SIZE - 1 - ((int)rayHitPos.y % TEXTURE_SIZE);
    }
}



/**
 * getUndistortedRayLength - Get the barrel-distortion corrected ray length for a given ray.
 *
 * @ray: The ray to undistort.
 *
 * Returns: The undistorted length of the ray.
 */
float getUndistortedRayLength(Vector3f* ray) {
    Vector3f undistortedRay;
    Vector3f proj = vectorProjection(ray, &viewplaneDir);
    undistortedRay = vectorSubtract(ray, &proj);

    return homogeneousVectorMagnitude(&undistortedRay);
}



/**
 * Render the scene.
 * This assumes that rays have already been cast.
 *
 * @gameData: Pointer to the game data structure.
 * Returns: nothing
 */
void renderProjectedScene(gameData *gameData) {
    int i;

    if (gameData->slowRenderMode) {
        int x, y;

        for(x = 0; x < WINDOW_WIDTH; x++)
            for(y = 0; y < WINDOW_HEIGHT; y++)
                gameData->screenBuffer[(WINDOW_WIDTH * y) + x] = 0xFFFFFFFF;
    }

    for(i = 0; i < WINDOW_WIDTH; i++) {
        int textureX = 0;
        int mapx, mapy;
        float drawLength;
        RayType rtype;
        Vector3f ray;

        if(homogeneousVectorMagnitude(&rays[i].hRay) < homogeneousVectorMagnitude(&rays[i].vRay)) {
            Vector3f coords;
            ray = rays[i].hRay;
            rtype = HORIZONTAL_RAY;

            coords = getTileCoordinateForHorizontalRay(&ray);
            mapx = coords.x;
            mapy = coords.y;
        } else {
            Vector3f coords;
            ray = rays[i].vRay;
            rtype = VERTICAL_RAY;

            coords = getTileCoordinateForVerticalRay(&ray);
            mapx = coords.x;
            mapy = coords.y;
        }

        if(gameData->textureMode)
            textureX = getTextureColumnNumberForRay(&ray, rtype);

        if(gameData->distortion)
            drawLength = calculateDrawHeight(homogeneousVectorMagnitude(&ray));
        else
            drawLength = calculateDrawHeight(getUndistortedRayLength(&ray));

        if(gameData->textureMode) {
            int texnum = MAP[mapy][mapx];
            if(texnum < 1 || texnum > 4)
                texnum = 4;
            drawTexturedStrip(gameData, i, (WINDOW_HEIGHT / 2.0f) - (drawLength / 2.0f), drawLength, textureX, gameData->TEXTURES[texnum - 1], rtype == HORIZONTAL_RAY);

        } else {
            int color = MAP[mapy][mapx];
            if(color < 1 || color > 4)
                color = 4;
            drawUntexturedStrip(gameData, i, (WINDOW_HEIGHT / 2.0f) - (drawLength / 2.0f), drawLength, gameData->COLORS[color - 1], rtype == HORIZONTAL_RAY);
        }
        if (gameData->slowRenderMode) {
            clearRenderer();
            displayFullscreenTexture(gameData->screenBuffer);
            SDL_Delay(2);
        }
    }
    if (gameData->slowRenderMode)
        gameData->slowRenderMode = 0;

    clearRenderer();
    displayFullscreenTexture(gameData->screenBuffer);
}
