#ifndef COMBAT_UI_H
#define COMBAT_UI_H

#include "player.h"
#include "enemy.h"
typedef struct win win_t;

enum type_win {start = 0, sp_player, hp_player, hp_enemy, end};

void state_display(const int win_y, const int len_y, const int len_x, const char *str,
		const int color, const enum type_win type, win_t **window);
win_t *display(const enum type_win type, win_t *window);
void free_display(win_t *window);
void refresh_fight(const int max_y, const int max_x, win_t *window,
		player_t *player, enemy_t *enemy);

#endif
