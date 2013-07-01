#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "bork.h"

void *Map_move(void *self, Direction direction)
{
	 assert(self != NULL);

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
	 assert(damage >= 0);
	 assert(self != NULL);

	 Map *map = self;
	 Room *location = map->location;
	 assert(map->location !=NULL);

	 return location->_(attack)(location, damage);
	 
}

int Map_init(void *self)
{
	 assert(self != NULL);
	 Map *map = self;

	 Room *entrance = NEW(Room, "The entrance to bork");
	 assert(entrance != NULL);

	 Room *hall = NEW(Room, "Hallway, there is a goblin here");
	 assert(hall != NULL);

	 Room *cell = NEW(Room, "A dungeon cell, it is dank and full of rats");
	 assert(cell != NULL);

	 Room *shrine = NEW(Room, "An altar to the gods resides here. There is nothing else here.");
	 assert(shrine != NULL);	 

	 Room *bakery = NEW(Room, "A pleasant aromatic smell drifts to your nose, or it would be if there wasn't a zombie maid there");
	 assert(bakery != NULL);

	 Room *teleporter = NEW(Room, "There's a teleportor to the east here, it looks as if it only goes one way");
	 
	 hall->bad_guy = NEW(Monster, "A goblin, he's picking his nose, gross");
	 assert(hall->bad_guy != NULL);

	 bakery->bad_guy = NEW(Monster, "An undead maid. Why would there be a maid in a dungeon bakery? No one knows");
	 assert(bakery != NULL);

	 entrance->south = hall;

	 hall->north = entrance;
	 hall->south = cell;

	 cell->south = teleporter;
	 cell->north = hall;
	 cell->east = shrine;

	 shrine->west = cell;

	 teleporter->east = bakery;

	 map->start = entrance;
	 map->location = entrance;

	 return 1;
	 
}

Object MapProto = {
	 .move = Map_move,
	 .attack = Map_attack,
	 .init = Map_init
};

int main(int argc, char *argv[])
{
	 srand(time(NULL));

	 // Reminder, enter description later
	 Map *game = NEW(Map, "");
	 assert(game != NULL);

	 printf("You enter the ");
	 game->location->_(describe)(game->location);
	 
	 while(process_input(game)) {
	 }

	 return 0;
	 
}
