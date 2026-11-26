#include "oscillator.h"
#include "still.h"
#include <stdlib.h>

void random_blinker(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);
        int vertical = rand() % 2;

        specific_blinker(grid, random_x, random_y, vertical);
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

void random_toad(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 3);
        int vertical = rand() % 2;

        specific_toad(grid, random_x, random_y, vertical);
    }
}

void specific_toad(Grid *grid, int x, int y, bool vertical) {
    if (grid->height < 4 || grid->width < 4) {
        return;
    }

    if (vertical) {
        grid_set(grid, x + 0, y + 0, true);
        grid_set(grid, x + 0, y + 1, true);
        grid_set(grid, x + 0, y + 2, true);
        grid_set(grid, x + 1, y + 1, true);
        grid_set(grid, x + 1, y + 2, true);
        grid_set(grid, x + 1, y + 3, true);
    } else {
        grid_set(grid, x + 0, y + 0, true);
        grid_set(grid, x + 1, y + 0, true);
        grid_set(grid, x + 2, y + 0, true);
        grid_set(grid, x + 1, y + 1, true);
        grid_set(grid, x + 2, y + 1, true);
        grid_set(grid, x + 3, y + 1, true);
    }
}

void random_beacon(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 3);

        specific_beacon(grid, random_x, random_y);
    }
}

void specific_beacon(Grid *grid, int x, int y) {
    if (grid->height < 4 || grid->width < 4) {
        return;
    }

    specific_block(grid, x, y);
    specific_block(grid, x + 2, y + 2);
}

void random_pulsar(Grid *grid, int count) {
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 12);
        int random_y = rand() % (grid->height - 12);

        specific_pulsar(grid, random_x, random_y);
    }
}

void specific_pulsar(Grid *grid, int x, int y) {
    if (grid->height < 13 || grid->width < 13) {
        return;
    }

    grid_set(grid, x + 2, y + 0, true);
    grid_set(grid, x + 3, y + 0, true);
    grid_set(grid, x + 4, y + 0, true);
    grid_set(grid, x + 2, y + 5, true);
    grid_set(grid, x + 3, y + 5, true);
    grid_set(grid, x + 4, y + 5, true);
    grid_set(grid, x + 0, y + 2, true);
    grid_set(grid, x + 0, y + 3, true);
    grid_set(grid, x + 0, y + 4, true);
    grid_set(grid, x + 5, y + 2, true);
    grid_set(grid, x + 5, y + 3, true);
    grid_set(grid, x + 5, y + 4, true);

    grid_set(grid, x + 8, y + 0, true);
    grid_set(grid, x + 9, y + 0, true);
    grid_set(grid, x + 10, y + 0, true);
    grid_set(grid, x + 12, y + 2, true);
    grid_set(grid, x + 12, y + 3, true);
    grid_set(grid, x + 12, y + 4, true);
    grid_set(grid, x + 7, y + 2, true);
    grid_set(grid, x + 7, y + 3, true);
    grid_set(grid, x + 7, y + 4, true);
    grid_set(grid, x + 8, y + 5, true);
    grid_set(grid, x + 9, y + 5, true);
    grid_set(grid, x + 10, y + 5, true);

    grid_set(grid, x + 2, y + 7, true);
    grid_set(grid, x + 3, y + 7, true);
    grid_set(grid, x + 4, y + 7, true);
    grid_set(grid, x + 2, y + 12, true);
    grid_set(grid, x + 3, y + 12, true);
    grid_set(grid, x + 4, y + 12, true);
    grid_set(grid, x + 0, y + 8, true);
    grid_set(grid, x + 0, y + 9, true);
    grid_set(grid, x + 0, y + 10, true);
    grid_set(grid, x + 5, y + 8, true);
    grid_set(grid, x + 5, y + 9, true);
    grid_set(grid, x + 5, y + 10, true);

    grid_set(grid, x + 8, y + 7, true);
    grid_set(grid, x + 9, y + 7, true);
    grid_set(grid, x + 10, y + 7, true);
    grid_set(grid, x + 8, y + 12, true);
    grid_set(grid, x + 9, y + 12, true);
    grid_set(grid, x + 10, y + 12, true);
    grid_set(grid, x + 7, y + 8, true);
    grid_set(grid, x + 7, y + 9, true);
    grid_set(grid, x + 7, y + 10, true);
    grid_set(grid, x + 12, y + 8, true);
    grid_set(grid, x + 12, y + 9, true);
    grid_set(grid, x + 12, y + 10, true);
}

void random_pentadelcathon(Grid *grid, int count) {

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);
        int vertical = rand() % 2;

        specific_pentadelcathon(grid, random_x, random_y, vertical);
    }
}

void specific_pentadelcathon(Grid *grid, int x, int y, bool vertical) {
    if (grid->width < 10 || grid->height < 10) {
        return;
    }

    if (vertical) {
        grid_set(grid, x + 1, y + 0, true);
        grid_set(grid, x + 1, y + 1, true);
        grid_set(grid, x + 0, y + 2, true);
        grid_set(grid, x + 2, y + 2, true);
        grid_set(grid, x + 1, y + 3, true);
        grid_set(grid, x + 1, y + 4, true);
        grid_set(grid, x + 1, y + 5, true);
        grid_set(grid, x + 1, y + 6, true);
        grid_set(grid, x + 0, y + 7, true);
        grid_set(grid, x + 2, y + 7, true);
        grid_set(grid, x + 1, y + 8, true);
        grid_set(grid, x + 1, y + 9, true);
    } else {
        grid_set(grid, x + 0, y + 1, true);
        grid_set(grid, x + 1, y + 1, true);
        grid_set(grid, x + 2, y + 0, true);
        grid_set(grid, x + 2, y + 2, true);
        grid_set(grid, x + 3, y + 1, true);
        grid_set(grid, x + 4, y + 1, true);
        grid_set(grid, x + 5, y + 1, true);
        grid_set(grid, x + 6, y + 1, true);
        grid_set(grid, x + 7, y + 0, true);
        grid_set(grid, x + 7, y + 2, true);
        grid_set(grid, x + 8, y + 1, true);
        grid_set(grid, x + 9, y + 1, true);
    }
}
