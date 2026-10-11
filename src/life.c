#include "life.h"
#include <stdlib.h>

Grid *grid_create(int width, int height) {
    Grid *grid = malloc(sizeof(Grid));
    if (grid == NULL) {
        return NULL;
    }
    grid->width = width;
    grid->height = height;
    grid->cells = malloc(width * height * sizeof(bool));
    if (grid->cells == NULL) {
        free(grid);
        return NULL;
    }

    for (int i = 0; i < width * height; i++) {
        grid->cells[i] = false;
    }

    return grid;
}

void grid_free(Grid *grid) {
    if (grid == NULL) {
        return;
    }

    free(grid->cells);
    free(grid);
}

bool grid_get(const Grid *grid, int x, int y) {
    return grid->cells[y * grid->width + x];
}

void grid_set(Grid *grid, int x, int y, bool alive) {
    grid->cells[y * grid->width + x] = alive;
}
