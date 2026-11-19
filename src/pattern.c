#include "pattern.h"
#include <stdlib.h>

void random_glider(Grid *grid, int count) {
    if (grid->width < 3 || grid->height < 3) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);

        grid_set(grid, random_x + 1, random_y + 0, true);
        grid_set(grid, random_x + 2, random_y + 1, true);
        grid_set(grid, random_x + 0, random_y + 2, true);
        grid_set(grid, random_x + 1, random_y + 2, true);
        grid_set(grid, random_x + 2, random_y + 2, true);
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

void random_block(Grid *grid, int count) {
    if (grid->width < 2 || grid->height < 2) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 1);
        int random_y = rand() % (grid->height - 1);

        grid_set(grid, random_x + 0, random_y + 0, true);
        grid_set(grid, random_x + 1, random_y + 0, true);
        grid_set(grid, random_x + 0, random_y + 1, true);
        grid_set(grid, random_x + 1, random_y + 1, true);
    }
}

void specific_block(Grid *grid, int x, int y) {
    if (grid->width < 2 || grid->height < 2) {
        return;
    }

    grid_set(grid, x + 0, y + 0, true);
    grid_set(grid, x + 1, y + 0, true);
    grid_set(grid, x + 0, y + 1, true);
    grid_set(grid, x + 1, y + 1, true);
}

void random_blinker(Grid *grid, int count) {
    if (grid->width < 3 || grid->height < 3) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);
        int vertical = rand() % 2;

        if (vertical) {
            grid_set(grid, random_x, random_y + 0, true);
            grid_set(grid, random_x, random_y + 1, true);
            grid_set(grid, random_x, random_y + 2, true);
        } else {
            grid_set(grid, random_x + 0, random_y, true);
            grid_set(grid, random_x + 1, random_y, true);
            grid_set(grid, random_x + 2, random_y, true);
        }
    }
}

void specific_blinker(Grid *grid, int x, int y, bool vertical) {
    if (grid->width < 3 || grid->height < 3) {
        return;
    }

    if (vertical) {
        grid_set(grid, x, y + 0, true);
        grid_set(grid, x, y + 1, true);
        grid_set(grid, x, y + 2, true);
    } else {
        grid_set(grid, x + 0, y, true);
        grid_set(grid, x + 1, y, true);
        grid_set(grid, x + 2, y, true);
    }
}
