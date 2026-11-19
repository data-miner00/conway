#ifndef PATTERN_H
#define PATTERN_H
#include "life.h"

void random_glider(Grid *grid, int count);
void specific_glider(Grid *grid, int x, int y);

void random_blinker(Grid *grid, int count);
void specific_blinker(Grid *grid, int x, int y, bool vertical);

#endif // PATTERN_H
