#ifndef _mech_h
#define _mech_h

#include "object.h"


struct Monster {
    Object proto;
    int hit_points;
};

typedef struct Monster Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);

Object MonsterProto;

struct Room {
    Object proto;

    Monster *bad_guy;

    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};

typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

Object RoomProto;

struct Map {
    Object proto;
    Room *start;
    Room *location;
};

typedef struct Map Map;

int process_input(Map *game);

#endif
