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

static bool is_in_bounds(const Grid *grid, int x, int y) {
    return x >= 0 && x < grid->width && y >= 0 && y < grid->height;
}

// no wrap around
bool grid_get(const Grid *grid, int x, int y) {
    if (!is_in_bounds(grid, x, y)) {
        return false;
    }

    return grid->cells[y * grid->width + x];
}

void grid_set(Grid *grid, int x, int y, bool alive) {
    if (!is_in_bounds(grid, x, y)) {
        return;
    }

    grid->cells[y * grid->width + x] = alive;
}

// can be simplified
int grid_count_neighbours(const Grid *grid, int x, int y) {
    int count = 0;

    // top
    if (grid_get(grid, x - 1, y - 1)) {
        count++;
    }
    if (grid_get(grid, x, y - 1)) {
        count++;
    }
    if (grid_get(grid, x + 1, y - 1)) {
        count++;
    }

    // same row
    if (grid_get(grid, x - 1, y)) {
        count++;
    }
    if (grid_get(grid, x + 1, y)) {
        count++;
    }

    // bottom
    if (grid_get(grid, x - 1, y + 1)) {
        count++;
    }
    if (grid_get(grid, x, y + 1)) {
        count++;
    }
    if (grid_get(grid, x + 1, y + 1)) {
        count++;
    }

    return count;
}
