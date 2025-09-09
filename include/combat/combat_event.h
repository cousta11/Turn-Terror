#ifndef FIGHT_EVENT_H
#define FIGHT_EVENT_H

#include "combat.h"
#include "combat_ui.h"

int change_of_state(const int modifier, int *current, int *maximum);
void event(int max_y, int max_x, enum type_win w, win_t **window,
		player_t *player, enemy_t *enemy);

#endif
