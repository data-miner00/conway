#include "spaceship.h"
#include <stdlib.h>

void random_glider(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);

        specific_glider(grid, random_x, random_y);
    }
}

void specific_glider(Grid *grid, int x, int y) {
    if (grid->width < 3 || grid->height < 3) {
        return;
    }

    grid_set(grid, x + 1, y + 0, true);
    grid_set(grid, x + 2, y + 1, true);
    grid_set(grid, x + 0, y + 2, true);
    grid_set(grid, x + 1, y + 2, true);
    grid_set(grid, x + 2, y + 2, true);
}

void random_lightweight_spaceship(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);

        specific_lightweight_spaceship(grid, random_x, random_y);
    }
}

void specific_lightweight_spaceship(Grid *grid, int x, int y) {
    if (grid->width < 5 || grid->height < 4) {
        return;
    }

    grid_set(grid, x + 1, y + 0, true);
    grid_set(grid, x + 2, y + 0, true);
    grid_set(grid, x + 3, y + 0, true);
    grid_set(grid, x + 4, y + 0, true);
    grid_set(grid, x + 0, y + 1, true);
    grid_set(grid, x + 4, y + 1, true);
    grid_set(grid, x + 4, y + 2, true);
    grid_set(grid, x + 0, y + 3, true);
    grid_set(grid, x + 3, y + 3, true);
}

void random_middleweight_spaceship(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);

        specific_middleweight_spaceship(grid, random_x, random_y);
    }
}

void specific_middleweight_spaceship(Grid *grid, int x, int y) {
    if (grid->width < 6 || grid->height < 5) {
        return;
    }

    grid_set(grid, x + 3, y + 0, true);
    grid_set(grid, x + 1, y + 1, true);
    grid_set(grid, x + 5, y + 1, true);
    grid_set(grid, x + 0, y + 2, true);
    grid_set(grid, x + 0, y + 3, true);
    grid_set(grid, x + 5, y + 3, true);
    grid_set(grid, x + 0, y + 4, true);
    grid_set(grid, x + 1, y + 4, true);
    grid_set(grid, x + 2, y + 4, true);
    grid_set(grid, x + 3, y + 4, true);
    grid_set(grid, x + 4, y + 4, true);
}
