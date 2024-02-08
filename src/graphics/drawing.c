#include "../../inc/graphics.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>


void setDrawColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(gInstance.renderer, r, g, b, a);
}

void drawLine(int x1, int y1, int x2, int y2) {
    int xOffset = 0;
    int yOffset = 0;

    if (x2 - x1 > 0) xOffset = -1;
    if (y2 - y1 > 0) yOffset = -1;

    SDL_RenderDrawLine(gInstance.renderer, x1, y1, x2 + xOffset, y2 + yOffset);
}

void fillRect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(gInstance.renderer, &rect);
}

void drawRect(int x, int y, int w, int h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(gInstance.renderer, &rect);
}

void presentRenderer() {
    SDL_RenderPresent(gInstance.renderer);
}

void clearRenderer() {
    SDL_RenderClear(gInstance.renderer);
}
