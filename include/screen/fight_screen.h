#ifndef FIGHT_SCREEN_H
#define FIGHT_SCREEN_H

#include "player_t.h"
#include "fight.h"
typedef struct win win_t;

enum type_win {start = 0, sp_player, hp_player, hp_enemy, end};

void hp_display(int win_y, int len_y, int len_x, char *str,
		int color, enum type_win type, win_t **window);
win_t *display(enum type_win type, win_t *window);
void free_display(win_t *window);
void refresh_fight(int max_y, int max_x, win_t *window, player_t *player,
		enemy_t *enemy);

#endif
