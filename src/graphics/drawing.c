#include "../../inc/graphics.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

/**
 * setDrawColor - Set the color used for drawing operations.
 *
 * @r: The red component of the color (0-255).
 * @g: The green component of the color (0-255).
 * @b: The blue component of the color (0-255).
 * @a: The alpha component of the color (0-255).
 *
 * This function sets the color used for drawing operations to the specified RGBA color.
 *
 * Return: void
 */
void setDrawColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(gInstance.renderer, r, g, b, a);
}

/**
 * drawLine - Draw a line between two points.
 *
 * @x1: The x-coordinate of the starting point.
 * @y1: The y-coordinate of the starting point.
 * @x2: The x-coordinate of the ending point.
 * @y2: The y-coordinate of the ending point.
 *
 * This function draws a line between the specified starting and ending points.
 *
 * Return: void
 */
void drawLine(int x1, int y1, int x2, int y2) {
    int xOffset = 0;
    int yOffset = 0;

    if (x2 - x1 > 0) xOffset = -1;
    if (y2 - y1 > 0) yOffset = -1;

    SDL_RenderDrawLine(gInstance.renderer, x1, y1, x2 + xOffset, y2 + yOffset);
}

/**
 * fillRect - Draw a filled rectangle.
 *
 * @x: The x-coordinate of the top-left corner of the rectangle.
 * @y: The y-coordinate of the top-left corner of the rectangle.
 * @w: The width of the rectangle.
 * @h: The height of the rectangle.
 *
 * This function draws a filled rectangle at the specified position and dimensions.
 *
 * Return: void
 */
void fillRect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(gInstance.renderer, &rect);
}

/**
 * drawRect - Draw a rectangle outline.
 *
 * @x: The x-coordinate of the top-left corner of the rectangle.
 * @y: The y-coordinate of the top-left corner of the rectangle.
 * @w: The width of the rectangle.
 * @h: The height of the rectangle.
 *
 * This function draws the outline of a rectangle at the specified position and dimensions.
 *
 * Return: void
 */
void drawRect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(gInstance.renderer, &rect);
}

/**
 * presentRenderer - Present the renderer's buffer to the window.
 *
 * This function presents the renderer's buffer to the associated window.
 *
 * Return: void
 */
void presentRenderer() {
    SDL_RenderPresent(gInstance.renderer);
}

/**
 * clearRenderer - Clear the renderer's buffer.
 *
 * This function clears the renderer's buffer.
 *
 * Return: void
 */
void clearRenderer() {
    SDL_RenderClear(gInstance.renderer);
}

