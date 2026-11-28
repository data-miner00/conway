#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "../life.h"

void random_glider(Grid *grid, int count);
void specific_glider(Grid *grid, int x, int y);

void random_lightweight_spaceship(Grid *grid, int count);
void specific_lightweight_spaceship(Grid *grid, int x, int y);

void random_middleweight_spaceship(Grid *grid, int count);
void specific_middleweight_spaceship(Grid *grid, int x, int y);

#endif // SPACESHIP_H
