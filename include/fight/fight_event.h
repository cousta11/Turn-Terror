#ifndef FIGHT_EVENT_H
#define FIGHT_EVENT_H

#include "fight.h"
#include "fight_screen.h"

int healing(int mod, int *hp, int *max_hp);
void event(int max_y, int max_x, enum type_win w, win_t **window,
		player_t *player, enemy_t *enemy);
enum type_win step(int max_y, int max_x, player_t *player, enemy_t *enemy);

#endif
