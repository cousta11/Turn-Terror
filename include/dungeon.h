#ifndef DUNGEON_H
#define DUNGEON_H

#include "main.h"
void dungeon_generated(int *start_y, int *start_x, int game_place[SIZE][SIZE]);
int out_the_barrier(int y, int x);
void preparing_the_dungeon(int max_y, int max_x,gamer *player, 
		int game_place[SIZE][SIZE]);

#endif
