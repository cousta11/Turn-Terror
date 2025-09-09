#ifndef DUNGEON_H
#define DUNGEON_H

#include "core.h"
#include "player.h"

int is_out_of_bounds(const int y, const int x);
void new_game(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE]);

#endif
