#ifndef COMBAT_H
#define COMBAT_H

#include "core.h"
#include "player.h"


int start_combat(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE]);

#endif
