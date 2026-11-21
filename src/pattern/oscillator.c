#include "still.h"
#include "oscillator.h"
#include <stdlib.h>

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

void random_toad(Grid *grid, int count) {
    if (grid->height < 4 || grid->width < 4) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 3);

        int vertical = rand() % 2;

        if (vertical) {
            grid_set(grid, random_x + 0, random_y + 0, true);
            grid_set(grid, random_x + 0, random_y + 1, true);
            grid_set(grid, random_x + 0, random_y + 2, true);
            grid_set(grid, random_x + 1, random_y + 1, true);
            grid_set(grid, random_x + 1, random_y + 2, true);
            grid_set(grid, random_x + 1, random_y + 3, true);
        } else {
            grid_set(grid, random_x + 0, random_y + 0, true);
            grid_set(grid, random_x + 1, random_y + 0, true);
            grid_set(grid, random_x + 2, random_y + 0, true);
            grid_set(grid, random_x + 1, random_y + 1, true);
            grid_set(grid, random_x + 2, random_y + 1, true);
            grid_set(grid, random_x + 3, random_y + 1, true);
        }
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
    if (grid->height < 4 || grid->width < 4) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 3);

        specific_block(grid, random_x, random_y);
        specific_block(grid, random_x + 2, random_y + 2);
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
    if (grid->height < 13 || grid->width < 13) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 12);
        int random_y = rand() % (grid->height - 12);

        grid_set(grid, random_x + 2, random_y + 0, true);
        grid_set(grid, random_x + 3, random_y + 0, true);
        grid_set(grid, random_x + 4, random_y + 0, true);
        grid_set(grid, random_x + 2, random_y + 5, true);
        grid_set(grid, random_x + 3, random_y + 5, true);
        grid_set(grid, random_x + 4, random_y + 5, true);
        grid_set(grid, random_x + 0, random_y + 2, true);
        grid_set(grid, random_x + 0, random_y + 3, true);
        grid_set(grid, random_x + 0, random_y + 4, true);
        grid_set(grid, random_x + 5, random_y + 2, true);
        grid_set(grid, random_x + 5, random_y + 3, true);
        grid_set(grid, random_x + 5, random_y + 4, true);

        grid_set(grid, random_x + 8, random_y + 0, true);
        grid_set(grid, random_x + 9, random_y + 0, true);
        grid_set(grid, random_x + 10, random_y + 0, true);
        grid_set(grid, random_x + 12, random_y + 2, true);
        grid_set(grid, random_x + 12, random_y + 3, true);
        grid_set(grid, random_x + 12, random_y + 4, true);
        grid_set(grid, random_x + 7, random_y + 2, true);
        grid_set(grid, random_x + 7, random_y + 3, true);
        grid_set(grid, random_x + 7, random_y + 4, true);
        grid_set(grid, random_x + 8, random_y + 5, true);
        grid_set(grid, random_x + 9, random_y + 5, true);
        grid_set(grid, random_x + 10, random_y + 5, true);

        grid_set(grid, random_x + 2, random_y + 7, true);
        grid_set(grid, random_x + 3, random_y + 7, true);
        grid_set(grid, random_x + 4, random_y + 7, true);
        grid_set(grid, random_x + 2, random_y + 12, true);
        grid_set(grid, random_x + 3, random_y + 12, true);
        grid_set(grid, random_x + 4, random_y + 12, true);
        grid_set(grid, random_x + 0, random_y + 8, true);
        grid_set(grid, random_x + 0, random_y + 9, true);
        grid_set(grid, random_x + 0, random_y + 10, true);
        grid_set(grid, random_x + 5, random_y + 8, true);
        grid_set(grid, random_x + 5, random_y + 9, true);
        grid_set(grid, random_x + 5, random_y + 10, true);

        grid_set(grid, random_x + 8, random_y + 7, true);
        grid_set(grid, random_x + 9, random_y + 7, true);
        grid_set(grid, random_x + 10, random_y + 7, true);
        grid_set(grid, random_x + 8, random_y + 12, true);
        grid_set(grid, random_x + 9, random_y + 12, true);
        grid_set(grid, random_x + 10, random_y + 12, true);
        grid_set(grid, random_x + 7, random_y + 8, true);
        grid_set(grid, random_x + 7, random_y + 9, true);
        grid_set(grid, random_x + 7, random_y + 10, true);
        grid_set(grid, random_x + 12, random_y + 8, true);
        grid_set(grid, random_x + 12, random_y + 9, true);
        grid_set(grid, random_x + 12, random_y + 10, true);
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
