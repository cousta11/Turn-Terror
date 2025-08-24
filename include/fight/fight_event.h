#ifndef FIGHT_EVENT_H
#define FIGHT_EVENT_H

#include "fight.h"
#include "screen.h"

int healing(int mod, int *hp, int *max_hp);
void event(int max_y, int max_x, enum type_win w, win_t **window, gamer *player,
		struct enemy *enemy);

#endif
