#include "life.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void print_grid(const Grid *grid) {
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            fputc(grid_get(grid, x, y) ? '#' : '.', stdout);
        }
        fputc('\n', stdout);
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    printf("Welcome to Conway's Game of Life!\n");

    Grid *grid = grid_create(20, 10);
    if (grid == NULL) {
        return 1;
    }

    // Glider
    grid_set(grid, 1, 0, true);
    grid_set(grid, 2, 1, true);
    grid_set(grid, 0, 2, true);
    grid_set(grid, 1, 2, true);
    grid_set(grid, 2, 2, true);

    // initial print
    print_grid(grid);

    int ch = getchar();
    if (ch == 'q' || ch == EOF) {
        grid_free(grid);
        return 0;
    }

    while (true) {
        // clear the screen
        printf("\033[2J");

        bool ok = grid_step(grid);
        if (!ok) {
            grid_free(grid);
            return 1;
        }

        print_grid(grid);

        ch = getchar();
        if (ch == 'q' || ch == EOF) {
            break;
        }
    }

    grid_free(grid);

    return 0;
}
