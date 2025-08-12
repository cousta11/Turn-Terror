#include <stdlib.h>
#include <string.h>

#include "control.h"
#include "fight.h"
#include "fight_event.h"
#include "screen.h"
#include "dungeon.h"
#include "who_enemy.h"


enum type_win fight_control(gamer *player, struct enemy *enemy)
{
	switch(getch()) {
		case QUIT_K: enemy->hp = 0; break;
		case DOWN_K: enemy->hp--; return hp_enemy; break;
		case RIGHT_K: player->hp--; return hp_player; break;
	}
	return end;
}
int fight(int max_y, int max_x, gamer *player, struct enemy *enemy)
{
	enum type_win step;
	win *window = NULL;
	clear();
	wattron(stdscr, COLOR_PAIR(2));
	mvaddstr(0, max_x/2 - strlen(enemy->name)/2, enemy->name);
	for(step = start; step < end; step++)
		event(max_y, max_x, step, &window, player, enemy);
	while(player->hp > 0 && enemy->hp > 0) {
		step = fight_control(player, enemy);
		event(max_y, max_x, step, &window, player, enemy);
	}
	free(enemy);
	free_display(window);
	if(player->hp <= 0)
		return 1;
	return 0;
}

int start_fight(int max_y, int max_x, gamer *player,
		int game_place[SIZE][SIZE])
{
	int i, j, k;
	int enemy[] = ENEMIES, s_enemy = sizeof(enemy)/sizeof(int);
	for(i = -2; i <= 2; i++) {
		for(j = -2; j <= 2; j++) {
			for(k = 0; k < s_enemy; k++) {
				if(out_the_barrier(player->y + i, player->x + j))
					continue;
				if(game_place[player->y + i][player->x + j] == enemy[k]) {
					game_place[player->y +i][player->x + j] = SPACE;
					if(fight(max_y, max_x, player, who_enemy(enemy[k])))
						return 1;
				}
			}
		}
	}
	scr_replay(max_y, max_x, player, game_place);
	return 0;
}
