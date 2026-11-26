#ifndef STILL_H
#define STILL_H
#include "../life.h"

void random_block(Grid *grid, int count);
void specific_block(Grid *grid, int x, int y);

void random_beehive(Grid *grid, int count);
void specific_beehive(Grid *grid, int x, int y);

void random_tub(Grid *grid, int count);
void specific_tub(Grid *grid, int x, int y);

void random_loaf(Grid *grid, int count);
void specific_loaf(Grid *grid, int x, int y);

void random_boat(Grid *grid, int count);
void specific_boat(Grid *grid, int x, int y);

void random_eater1(Grid *grid, int count);
void specific_eater1(Grid *grid, int x, int y);

#endif // STILL_H
