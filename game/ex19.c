#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ex19.h"
#include <assert.h>

void *Map_move(void *self, Direction direction)
{
	 assert(self != NULL);

	 // Should always be in some valid location
	 Map *map = self;
	 Room *location = map->location;
	 Room *next = NULL;
	 assert(map->location != NULL);
	 
	 next = location->_(move)(location, direction);

	 if(next) {
		  map->location = next;
	 }
	 
	 return next;
}

int Map_attack(void *self, int damage)
{
	 assert(self != NULL);
	 assert(damage >= 0);
	 
	 Map* map = self;
	 Room *location = map->location;
	 assert(map->location != NULL);
	 
	 return location->_(attack)(location, damage);
}


int Map_init(void *self)
{
	 assert(self != NULL);
	 Map *map = self;

	 // make some rooms for a small map
	 Room *hall = NEW(Room, "The great Hall");
	 assert(hall != NULL);

	 Room *throne = NEW(Room, "The throne room");
	 assert(throne != NULL);

	 Room *arena = NEW(Room, "The arena, with the minotaur");
	 assert(arena != NULL);

	 Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
	 assert(kitchen);

	 Room *pantry = NEW(Room, "A pantry, it smells of jerky and of the goblin there");
	 
	 // put the bad guy in the arena
	 arena->bad_guy = NEW(Monster, "The evil minotaur");
	 assert(arena->bad_guy != NULL);

	 pantry->bad_guy = NEW(Monster, "A scraggly goblin");
	 assert(pantry->bad_guy != NULL);

     // setup the map rooms
	 hall->north = throne;

	 throne->west = arena;
	 throne->east = kitchen;
	 throne->south = hall;

	 arena->east = throne;
	 kitchen->west = throne;

	 kitchen->north = pantry;

	 pantry->south = kitchen;

	 // start the map and the character off in the hall
	 map->start = hall;
	 map->location = hall;

	 return 1;
}

Object MapProto = {
	 .init = Map_init,
	 .move = Map_move,
	 .attack = Map_attack
};


int main(int argc, char *argv[])
{
	 // simple way to setup the randomness
	 srand(time(NULL));

	 // make our map to work with
	 Map *game = NEW(Map, "The Hall of the Minotaur.");
	 assert(game != NULL);
	 
	 printf("You enter the ");
	 game->location->_(describe)(game->location);

	 while(process_input(game)) {
	 }

	 return 0;
}
