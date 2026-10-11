#include "life.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Builds a grid from rows of text: '#' is a live cell, anything else is a dead one.
static Grid *grid_from(int width, int height, const char *rows[]) {
    Grid *grid = grid_create(width, height);
    assert(grid != NULL);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid_set(grid, x, y, rows[y][x] == '#');
        }
    }

    return grid;
}

// Stops the test, after printing both pictures, unless the grid matches the rows of text.
static void expect_grid(const char *label, const Grid *grid, int width, int height,
                        const char *rows[]) {
    bool same = true;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (grid_get(grid, x, y) != (rows[y][x] == '#')) {
                same = false;
            }
        }
    }
    if (same) {
        return;
    }

    fprintf(stderr, "%s\nexpected:\n", label);
    for (int y = 0; y < height; y++) {
        fprintf(stderr, "  %s\n", rows[y]);
    }
    fprintf(stderr, "but the grid is:\n");
    for (int y = 0; y < height; y++) {
        fputs("  ", stderr);
        for (int x = 0; x < width; x++) {
            fputc(grid_get(grid, x, y) ? '#' : '.', stderr);
        }
        fputc('\n', stderr);
    }
    abort();
}

// Advances one generation and insists that it worked.
static void step(Grid *grid) {
    bool ok = grid_step(grid);
    assert(ok);
}

// The pictures in the tests below are laid out by hand, one row of the grid per line.
// clang-format off

// A live cell with fewer than two live neighbours dies.
static void test_lonely_cell_dies(void) {
    const char *before[] = {
        "...",
        ".#.",
        "...",
    };
    const char *after[] = {
        "...",
        "...",
        "...",
    };

    Grid *grid = grid_from(3, 3, before);
    step(grid);
    expect_grid("lonely cell", grid, 3, 3, after);
    grid_free(grid);
}

// A dead cell with exactly three live neighbours is born, and live cells with two live
// neighbours stay alive.
static void test_three_neighbours_give_birth(void) {
    const char *before[] = {
        "##.",
        "#..",
        "...",
    };
    const char *after[] = {
        "##.",
        "##.",
        "...",
    };

    Grid *grid = grid_from(3, 3, before);
    step(grid);
    expect_grid("corner of three", grid, 3, 3, after);
    grid_free(grid);
}

// A live cell with more than three live neighbours dies. The centre of the plus has four.
static void test_crowded_cell_dies(void) {
    const char *before[] = {
        ".....",
        "..#..",
        ".###.",
        "..#..",
        ".....",
    };
    const char *after[] = {
        ".....",
        ".###.",
        ".#.#.",
        ".###.",
        ".....",
    };

    Grid *grid = grid_from(5, 5, before);
    step(grid);
    expect_grid("plus", grid, 5, 5, after);
    grid_free(grid);
}

// A block never changes.
static void test_block_stays_still(void) {
    const char *block[] = {
        "....",
        ".##.",
        ".##.",
        "....",
    };

    Grid *grid = grid_from(4, 4, block);
    step(grid);
    expect_grid("block after 1 step", grid, 4, 4, block);
    step(grid);
    expect_grid("block after 2 steps", grid, 4, 4, block);
    grid_free(grid);
}

// A blinker flips between a horizontal and a vertical line. This only works if every cell's
// new state comes from the grid as it was before the step.
static void test_blinker_flips_every_step(void) {
    const char *horizontal[] = {
        ".....",
        ".....",
        ".###.",
        ".....",
        ".....",
    };
    const char *vertical[] = {
        ".....",
        "..#..",
        "..#..",
        "..#..",
        ".....",
    };

    Grid *grid = grid_from(5, 5, horizontal);
    step(grid);
    expect_grid("blinker after 1 step", grid, 5, 5, vertical);
    step(grid);
    expect_grid("blinker after 2 steps", grid, 5, 5, horizontal);
    grid_free(grid);
}

// After four steps a glider has the same shape, one cell down and one cell to the right.
static void test_glider_moves_diagonally(void) {
    const char *before[] = {
        ".#....",
        "..#...",
        "###...",
        "......",
        "......",
        "......",
    };
    const char *after[] = {
        "......",
        "..#...",
        "...#..",
        ".###..",
        "......",
        "......",
    };

    Grid *grid = grid_from(6, 6, before);
    for (int i = 0; i < 4; i++) {
        step(grid);
    }
    expect_grid("glider after 4 steps", grid, 6, 6, after);
    grid_free(grid);
}

// clang-format on

int main(void) {
    test_lonely_cell_dies();
    test_three_neighbours_give_birth();
    test_crowded_cell_dies();
    test_block_stays_still();
    test_blinker_flips_every_step();
    test_glider_moves_diagonally();
    return 0;
}
