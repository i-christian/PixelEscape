#include "../../inc/main.h"

short MAP[MAP_GRID_HEIGHT][MAP_GRID_HEIGHT];

/**
 * readMapFromFile - Function to read the map from file and generate the color map array
 * @filename: The name of the file to be read
 * @color_map: The array to store the color map
 *
 * Description: This function reads the content of the file specified by filename in binary mode and
 * stores it into the color_map array.
 *
 * Return: This function does not return any value.
 */

void readMapFromFile(const char *filename, short color_map[MAP_GRID_HEIGHT][MAP_GRID_WIDTH]) {
    // Open file for reading in binary mode
    SDL_RWops* file = SDL_RWFromFile(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file for reading: %s\n", SDL_GetError());
        return;
    }

    /* Read the content of the file into the map array */
    SDL_RWread(file, color_map, sizeof(short), MAP_GRID_HEIGHT * MAP_GRID_WIDTH);

    // Close the file
    SDL_RWclose(file);
}
