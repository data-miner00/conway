#include "still.h"
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

void random_beehive(Grid *grid, int count) {
    if (grid->width < 4 || grid->height < 3) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 2);

        grid_set(grid, random_x + 1, random_y + 0, true);
        grid_set(grid, random_x + 2, random_y + 0, true);
        grid_set(grid, random_x + 0, random_y + 1, true);
        grid_set(grid, random_x + 3, random_y + 1, true);
        grid_set(grid, random_x + 1, random_y + 2, true);
        grid_set(grid, random_x + 2, random_y + 2, true);
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
    if (grid->width < 3 || grid->height < 3) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);

        grid_set(grid, random_x + 1, random_y + 0, true);
        grid_set(grid, random_x + 0, random_y + 1, true);
        grid_set(grid, random_x + 2, random_y + 1, true);
        grid_set(grid, random_x + 1, random_y + 2, true);
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
    if (grid->width < 4 || grid->height < 4) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 3);

        grid_set(grid, random_x + 1, random_y + 0, true);
        grid_set(grid, random_x + 2, random_y + 0, true);
        grid_set(grid, random_x + 0, random_y + 1, true);
        grid_set(grid, random_x + 3, random_y + 1, true);
        grid_set(grid, random_x + 1, random_y + 2, true);
        grid_set(grid, random_x + 3, random_y + 2, true);
        grid_set(grid, random_x + 2, random_y + 3, true);
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
    if (grid->width < 3 || grid->height < 3) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 2);
        int random_y = rand() % (grid->height - 2);

        grid_set(grid, random_x + 0, random_y + 0, true);
        grid_set(grid, random_x + 1, random_y + 0, true);
        grid_set(grid, random_x + 0, random_y + 1, true);
        grid_set(grid, random_x + 2, random_y + 1, true);
        grid_set(grid, random_x + 1, random_y + 2, true);
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
    if (grid->width < 4 || grid->height < 4) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int random_x = rand() % (grid->width - 3);
        int random_y = rand() % (grid->height - 3);

        grid_set(grid, random_x + 0, random_y + 0, true);
        grid_set(grid, random_x + 1, random_y + 0, true);
        grid_set(grid, random_x + 0, random_y + 1, true);

        grid_set(grid, random_x + 2, random_y + 1, true);
        grid_set(grid, random_x + 2, random_y + 2, true);
        grid_set(grid, random_x + 2, random_y + 3, true);
        grid_set(grid, random_x + 3, random_y + 3,
                 true); // if 3 replaced with 4, will produce good generation
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
