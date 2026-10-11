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

// Makes every cell of a width x height grid alive.
static void fill(Grid *grid, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            grid_set(grid, x, y, true);
        }
    }
}

// Positions off the board are always dead, even when every real cell is alive.
static void test_get_off_board_is_dead(void) {
    Grid *grid = grid_create(5, 3);
    fill(grid, 5, 3);

    assert(grid_get(grid, -1, 0) == false);
    assert(grid_get(grid, 5, 0) == false);
    assert(grid_get(grid, 0, -1) == false);
    assert(grid_get(grid, 0, 3) == false);

    grid_free(grid);
}

// Setting a position off the board changes nothing.
static void test_set_off_board_does_nothing(void) {
    Grid *grid = grid_create(5, 3);

    grid_set(grid, -1, 0, true);
    grid_set(grid, 5, 0, true);
    grid_set(grid, 0, -1, true);
    grid_set(grid, 0, 3, true);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 5; x++) {
            assert(grid_get(grid, x, y) == false);
        }
    }

    grid_free(grid);
}

// On an empty grid nobody has live neighbours.
static void test_empty_grid_has_no_neighbours(void) {
    Grid *grid = grid_create(5, 3);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 5; x++) {
            assert(grid_count_neighbours(grid, x, y) == 0);
        }
    }

    grid_free(grid);
}

// A live cell is not its own neighbour.
static void test_cell_does_not_count_itself(void) {
    Grid *grid = grid_create(5, 3);

    grid_set(grid, 2, 1, true);
    assert(grid_count_neighbours(grid, 2, 1) == 0);

    grid_free(grid);
}

// Each of the eight positions around a cell counts, diagonals included, and nothing further
// away does.
static void test_each_of_the_eight_neighbours_counts(void) {
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) {
                continue;
            }

            Grid *grid = grid_create(5, 3);
            grid_set(grid, 2 + dx, 1 + dy, true);
            assert(grid_count_neighbours(grid, 2, 1) == 1);
            grid_free(grid);
        }
    }

    Grid *grid = grid_create(5, 3);
    grid_set(grid, 0, 1, true);
    grid_set(grid, 4, 1, true);
    assert(grid_count_neighbours(grid, 2, 1) == 0);
    grid_free(grid);
}

// With every cell alive, the count is simply how many neighbours are on the board:
// 8 in the middle, 5 along an edge, 3 in a corner.
static void test_off_board_positions_count_as_dead(void) {
    Grid *grid = grid_create(5, 3);
    fill(grid, 5, 3);

    assert(grid_count_neighbours(grid, 2, 1) == 8);

    assert(grid_count_neighbours(grid, 2, 0) == 5);
    assert(grid_count_neighbours(grid, 2, 2) == 5);
    assert(grid_count_neighbours(grid, 0, 1) == 5);
    assert(grid_count_neighbours(grid, 4, 1) == 5);

    assert(grid_count_neighbours(grid, 0, 0) == 3);
    assert(grid_count_neighbours(grid, 4, 0) == 3);
    assert(grid_count_neighbours(grid, 0, 2) == 3);
    assert(grid_count_neighbours(grid, 4, 2) == 3);

    grid_free(grid);
}

// (0, 1) is the first cell of the second row. It sits right after (4, 0) in memory, but on the
// board it is nowhere near it.
static void test_right_edge_is_not_next_to_left_edge(void) {
    Grid *grid = grid_create(5, 3);

    grid_set(grid, 0, 1, true);
    assert(grid_count_neighbours(grid, 4, 0) == 0);

    grid_free(grid);
}

int main(void) {
    test_new_grid_is_all_dead();
    test_set_then_get();
    test_each_cell_is_independent();
    test_two_grids_do_not_share_cells();
    test_free_accepts_null();

    test_get_off_board_is_dead();
    test_set_off_board_does_nothing();
    test_empty_grid_has_no_neighbours();
    test_cell_does_not_count_itself();
    test_each_of_the_eight_neighbours_counts();
    test_off_board_positions_count_as_dead();
    test_right_edge_is_not_next_to_left_edge();
    return 0;
}
