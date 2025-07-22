#ifndef FIGHT_H
#define FIGHT_H

#include "main.h"
int fight(int max_y, int max_x, int enemy_y, int enemy_x,
		gamer *player, int game_place[SIZE][SIZE]);
int start_fight(const int y, const int x, int *enemy_y, int *enemy_x,
		const int game_place[SIZE][SIZE]);

#endif
