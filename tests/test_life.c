#include "life.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

// A brand new grid has no live cells.
static void test_new_grid_is_all_dead(void) {
    Grid *grid = grid_create(5, 3);
    assert(grid != NULL);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 5; x++) {
            assert(grid_get(grid, x, y) == false);
        }
    }

    grid_free(grid);
}

// What you set is what you get back, and you can change it again.
static void test_set_then_get(void) {
    Grid *grid = grid_create(5, 3);

    grid_set(grid, 4, 2, true);
    assert(grid_get(grid, 4, 2) == true);

    grid_set(grid, 4, 2, false);
    assert(grid_get(grid, 4, 2) == false);

    grid_free(grid);
}

// Setting one cell must not change any other cell. The grid is deliberately not square, so
// mixing up x and y, or width and height, gets caught.
static void test_each_cell_is_independent(void) {
    const int width = 5;
    const int height = 3;

    for (int set_y = 0; set_y < height; set_y++) {
        for (int set_x = 0; set_x < width; set_x++) {
            Grid *grid = grid_create(width, height);
            grid_set(grid, set_x, set_y, true);

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    bool expected = (x == set_x && y == set_y);
                    assert(grid_get(grid, x, y) == expected);
                }
            }

            grid_free(grid);
        }
    }
}

// Two grids each have their own cells.
static void test_two_grids_do_not_share_cells(void) {
    Grid *first = grid_create(4, 4);
    Grid *second = grid_create(4, 4);

    grid_set(first, 1, 2, true);
    assert(grid_get(first, 1, 2) == true);
    assert(grid_get(second, 1, 2) == false);

    grid_free(first);
    grid_free(second);
}

// Like free(), grid_free() accepts NULL and does nothing.
static void test_free_accepts_null(void) {
    grid_free(NULL);
}

int main(void) {
    test_new_grid_is_all_dead();
    test_set_then_get();
    test_each_cell_is_independent();
    test_two_grids_do_not_share_cells();
    test_free_accepts_null();
    return 0;
}
