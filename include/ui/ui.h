#ifndef SCREEN_H
#define SCREEN_H

#include "player.h"
#include "core.h"

int init_ui(int *max_y, int *max_x, int work_bw);
void scr_replay(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE]);
void move_player(const int mod_y, const int mod_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE]);

int winner_screen(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE]);
int lose_screen(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE]);

#endif
