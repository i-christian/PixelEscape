#ifndef MAP_H
#define MAP_H
#include "game_data.h"

/* Functions */

void renderOverheadMap(gameData *gameData);
void readMapFromFile(const char *filename, short color_map[MAP_GRID_HEIGHT][MAP_GRID_WIDTH]);

#endif /* MAP_H */
