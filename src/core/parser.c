#include "../../inc/main.h"
#include <errno.h>


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
void readMapFromFile(const char *filename, short map[MAP_GRID_HEIGHT][MAP_GRID_WIDTH])
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file for reading: %s\n", strerror(errno));
        return;
    }

    for (int i = 0; i < MAP_GRID_HEIGHT; ++i) {
        for (int j = 0; j < MAP_GRID_WIDTH; ++j) {
            fscanf(file, "%hd", &map[i][j]);
        }
    }

    fclose(file);
}
