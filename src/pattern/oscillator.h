#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include "../life.h"

void random_blinker(Grid *grid, int count);
void specific_blinker(Grid *grid, int x, int y, bool vertical);

void random_toad(Grid *grid, int count);
void specific_toad(Grid *grid, int x, int y, bool vertical);

void random_beacon(Grid *grid, int count);
void specific_beacon(Grid *grid, int x, int y);

#endif // OSCILLATOR_H
