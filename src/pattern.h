#ifndef PATTERN_H
#define PATTERN_H
#include "life.h"

// Still lifes
void random_glider(Grid *grid, int count);
void specific_glider(Grid *grid, int x, int y);

void random_block(Grid *grid, int count);
void specific_block(Grid *grid, int x, int y);

void random_beehive(Grid *grid, int count);
void specific_beehive(Grid *grid, int x, int y);

void random_tub(Grid *grid, int count);
void specific_tub(Grid *grid, int x, int y);

// Oscillators
void random_blinker(Grid *grid, int count);
void specific_blinker(Grid *grid, int x, int y, bool vertical);

#endif // PATTERN_H
