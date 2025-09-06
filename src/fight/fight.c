#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "screen.h"
#include "fight.h"
#include "fight_event.h"
#include "dungeon.h"
#include "who_enemy.h"


int fight(int max_y, int max_x, gamer *player, struct enemy *enemy)
{
	enum type_win event_type;
	win_t *window = NULL;
	clear();
	wattron(stdscr, COLOR_PAIR(2));
	mvaddstr(0, max_x/2 - strlen(enemy->name)/2, enemy->name);
	refresh_fight(max_y, max_x, window, player, enemy);
	while(player->hp > 0 && enemy->hp > 0) {
		event_type = step(max_y, max_x, player, enemy);
		event(max_y, max_x, event_type, &window, player, enemy);
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
