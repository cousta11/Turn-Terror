#ifndef FIGHT_H
#define FIGHT_H

#include "main.h"

struct enemy {
	char *name;
	int hp, max_hp;
	int dmg, armor;
};
typedef struct win win_t;

int start_fight(int max_y, int max_x, gamer *player,
		int game_place[MAP_SIZE][MAP_SIZE]);
void refresh_fight(int max_y, int max_x, win_t *window, gamer *player,
		struct enemy *enemy);

#endif
