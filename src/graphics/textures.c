#include "../../inc/graphics.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>


/**
 * generateXorTexture - Generate an XOR texture of the specified size with given color masks.
 *
 * @size: The size of the texture.
 * @redmask: The mask for the red color component.
 * @greenmask: The mask for the green color component.
 * @bluemask: The mask for the blue color component.
 *
 * Returns: A pointer to the generated texture.
 */
Uint32* generateXorTexture(int size, int redmask, int greenmask, int bluemask) {
    int x, y;
    float factor = 256.0f / (float)size;
    Uint32* texture = createTexture(size, size);

    for(x = 0; x < size; x++)
        for(y = 0; y < size; y++)
            texture[(size * y) + x] = RGBtoABGR((int)((x ^ y) * factor) & redmask, (int)((x ^ y) * factor) & greenmask, (int)((x ^ y) * factor) & bluemask);

    return (texture);
}



/**
 * generateGreenXorTexture - Generate an XOR texture of the specified size with red color.
 *
 * @size: The size of the texture.
 *
 * Return: A pointer to the generated texture.
 */
Uint32* generateRedXorTexture(int size) {
    return (generateXorTexture(size, 0xFF, 0x00, 0x00));
}



/**
 * generateBlueXorTexture - Generate an XOR texture of the specified size with green color.
 *
 * @size: The size of the texture.
 *
 * Return: A pointer to the generated texture.
 */
Uint32* generateGreenXorTexture(int size) {
    return (generateXorTexture(size, 0x00, 0xFF, 0x00));
}


/**
 * generateBlueXorTexture - Generate an XOR texture of the specified size with blue color.
 *
 * @param size: The size of the texture.
 *
 * Return: A pointer to the generated texture.
 */
Uint32* generateBlueXorTexture(int size) {
    return (generateXorTexture(size, 0x00, 0x00, 0xFF));
}


/**
 * generateGrayXorTexture - Generate an XOR texture of the specified size with gray color.
 *
 * @param size: The size of the texture.
 *
 * Return: A pointer to the generated texture.
 */
Uint32* generateGrayXorTexture(int size) {
    return (generateXorTexture(size, 0xFF, 0xFF, 0xFF));
}
