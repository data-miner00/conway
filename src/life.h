#ifndef LIFE_H
#define LIFE_H

#include <stdbool.h>

// One Game of Life board: `width` columns by `height` rows of cells, each alive or dead.
typedef struct {
    int width;
    int height;
    bool *cells;
} Grid;

// Makes a new grid with every cell dead. Returns NULL if the memory could not be allocated.
// The caller owns the grid and must pass it to grid_free() when finished with it.
Grid *grid_create(int width, int height);

// Releases everything grid_create() allocated. The grid must not be used afterwards.
// Passing NULL is allowed and does nothing, like free().
void grid_free(Grid *grid);

// Is the cell at column x, row y alive? (0, 0) is the top-left corner.
// A position that is off the board is dead.
bool grid_get(const Grid *grid, int x, int y);

// Makes the cell at column x, row y alive or dead. Does nothing if the position is off the
// board.
void grid_set(Grid *grid, int x, int y, bool alive);

// How many of the eight cells around column x, row y are alive? Positions that are off the
// board count as dead. The cell at (x, y) itself is not counted.
int grid_count_neighbours(const Grid *grid, int x, int y);

#endif
