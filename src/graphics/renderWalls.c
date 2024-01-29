#include "../../inc/main.h"
#define MAP_HEIGHT 5
#define MAP_WIDTH 5
#define M_PI 3.14159265358979323846

void renderWalls(SDL_Instance *gInstance) {
    // Define map
    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1}
    };
}
