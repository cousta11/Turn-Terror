#ifndef DANGEON_H
#define DANGEON_H

#include "sup_func.h"
void dangeon_genereted(int *start_y, int *start_x, int game_place[SIZE][SIZE]);
int out_the_barrier(int y, int x);
void preparing_the_dungeon(int max_y, int max_x, int game_place[SIZE][SIZE],
		gamer *player);

#endif
