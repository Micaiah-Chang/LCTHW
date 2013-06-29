#ifndef _ex19_h
#define _ex19_h

#include "object.h"
#include "mechanics.h"


void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);

#endif

