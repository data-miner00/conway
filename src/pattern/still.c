#include "still.h"
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

void random_block(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 1);
        int random_y = rand() % (grid->height - 1);

        specific_block(grid, random_x, random_y);
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

void random_beehive(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 2);

        specific_beehive(grid, random_x, random_y);
    }
}

void specific_beehive(Grid *grid, int x, int y) {
    if (grid->width < 4 || grid->height < 3) {
        return;
    }

    grid_set(grid, x + 1, y + 0, true);
    grid_set(grid, x + 2, y + 0, true);
    grid_set(grid, x + 0, y + 1, true);
    grid_set(grid, x + 3, y + 1, true);
    grid_set(grid, x + 1, y + 2, true);
    grid_set(grid, x + 2, y + 2, true);
}

void random_tub(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);

        specific_tub(grid, random_x, random_y);
    }
}

void specific_tub(Grid *grid, int x, int y) {
    if (grid->width < 3 || grid->height < 3) {
        return;
    }

    grid_set(grid, x + 1, y + 0, true);
    grid_set(grid, x + 0, y + 1, true);
    grid_set(grid, x + 2, y + 1, true);
    grid_set(grid, x + 1, y + 2, true);
}

void random_loaf(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 3);

        specific_loaf(grid, random_x, random_y);
    }
}

void specific_loaf(Grid *grid, int x, int y) {
    if (grid->width < 4 || grid->height < 4) {
        return;
    }

    grid_set(grid, x + 1, y + 0, true);
    grid_set(grid, x + 2, y + 0, true);
    grid_set(grid, x + 0, y + 1, true);
    grid_set(grid, x + 3, y + 1, true);
    grid_set(grid, x + 1, y + 2, true);
    grid_set(grid, x + 3, y + 2, true);
    grid_set(grid, x + 2, y + 3, true);
}

void random_boat(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);

        specific_boat(grid, random_x, random_y);
    }
}

void specific_boat(Grid *grid, int x, int y) {
    if (grid->width < 3 || grid->height < 3) {
        return;
    }

    grid_set(grid, x + 0, y + 0, true);
    grid_set(grid, x + 1, y + 0, true);
    grid_set(grid, x + 0, y + 1, true);
    grid_set(grid, x + 2, y + 1, true);
    grid_set(grid, x + 1, y + 2, true);
}

void random_eater1(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 3);

        specific_eater1(grid, random_x, random_y);
    }
}

void specific_eater1(Grid *grid, int x, int y) {
    if (grid->width < 4 || grid->height < 4) {
        return;
    }

    grid_set(grid, x + 0, y + 0, true);
    grid_set(grid, x + 1, y + 0, true);
    grid_set(grid, x + 0, y + 1, true);

    grid_set(grid, x + 2, y + 1, true);
    grid_set(grid, x + 2, y + 2, true);
    grid_set(grid, x + 2, y + 3, true);
    grid_set(grid, x + 3, y + 3, true);
}
