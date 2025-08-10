#ifndef FIGHT_EVENT_H
#define FIGHT_EVENT_H

#include "fight.h"

int healing(int mod, int *hp, int *max_hp);
void event(int max_y, int max_x, enum type_win w, win **window, gamer *player,
		struct enemy *enemy);

#endif
