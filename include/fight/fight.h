#ifndef FIGHT_H
#define FIGHT_H

#include "main.h"

typedef struct enemy_t {
	char *name;
	int hp, max_hp;
	int dmg, armor;
} enemy_t;

int start_fight(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE]);

#endif
