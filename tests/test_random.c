#include "life.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

// How many cells of the grid are alive?
static int count_alive(const Grid *grid) {
    int alive = 0;
    for (int y = 0; y < grid->height; y++) {
        for (int x = 0; x < grid->width; x++) {
            if (grid_get(grid, x, y)) {
                alive++;
            }
        }
    }
    return alive;
}

// 0 percent kills every cell, even cells that were alive before. The grid is not square, so
// mixing up x and y, or width and height, gets caught.
static void test_zero_percent_kills_every_cell(void) {
    Grid *grid = grid_create(7, 5);
    assert(grid != NULL);
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 7; x++) {
            grid_set(grid, x, y, true);
        }
    }

    grid_fill_random(grid, 0);
    assert(count_alive(grid) == 0);

    grid_free(grid);
}

// 100 percent makes every cell alive.
static void test_hundred_percent_fills_every_cell(void) {
    Grid *grid = grid_create(7, 5);
    assert(grid != NULL);

    grid_fill_random(grid, 100);
    assert(count_alive(grid) == 7 * 5);

    grid_free(grid);
}

// 25 percent of 10,000 cells is 2,500. Chance makes it a little more or less each time, but
// with this many cells it lands well inside 2,000 to 3,000.
static void test_quarter_is_roughly_a_quarter(void) {
    Grid *grid = grid_create(100, 100);
    assert(grid != NULL);

    grid_fill_random(grid, 25);
    int alive = count_alive(grid);
    if (alive < 2000 || alive > 3000) {
        fprintf(stderr, "25 percent of 10000 cells gave %d alive\n", alive);
    }
    assert(alive >= 2000 && alive <= 3000);

    grid_free(grid);
}

// Two fills straight after each other give different boards. If they come out the same,
// something keeps restarting the random numbers from the same point.
static void test_two_fills_are_different(void) {
    Grid *first = grid_create(100, 100);
    Grid *second = grid_create(100, 100);
    assert(first != NULL && second != NULL);

    grid_fill_random(first, 50);
    grid_fill_random(second, 50);

    bool any_different = false;
    for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 100; x++) {
            if (grid_get(first, x, y) != grid_get(second, x, y)) {
                any_different = true;
            }
        }
    }
    assert(any_different);

    grid_free(first);
    grid_free(second);
}

int main(void) {
    test_zero_percent_kills_every_cell();
    test_hundred_percent_fills_every_cell();
    test_quarter_is_roughly_a_quarter();
    test_two_fills_are_different();
    return 0;
}
