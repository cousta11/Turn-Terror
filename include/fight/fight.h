#ifndef FIGHT_H
#define FIGHT_H

#include "main.h"
struct enemy {
	char *name;
	int hp, max_hp;
};
int start_fight(int max_y, int max_x, gamer *player,
		int game_place[SIZE][SIZE]);

#endif
