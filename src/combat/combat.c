#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "combat_ui.h"
#include "combat_step.h"
#include "combat.h"
#include "combat_event.h"
#include "dungeon.h"
#include "who_enemy.h"

#define SEARCH_RADIUS 2

static int fight(const int max_y, const int max_x, player_t *player,
		enemy_t *enemy)
{
	enum type_win event_type;
	win_t *window = NULL;

	clear();
	wattron(stdscr, COLOR_PAIR(2));
	mvaddstr(0, max_x/2 - strlen(enemy->name)/2, enemy->name);
	refresh_fight(max_y, max_x, &window, player, enemy);

	while(player->hp > 0 && enemy->hp > 0) {
		event_type = step(max_y, max_x, player, enemy);
		event(max_y, max_x, sp_player, &window, player, enemy);
		event(max_y, max_x, event_type, &window, player, enemy);
	}

	free(enemy);
	free_display(window);

	if(player->hp <= 0)
		return 1;
	return 0;
}

int start_combat(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	int i, j, k;
	int enemy[] = ENEMIES, enemy_count = sizeof(enemy)/sizeof(int);

	for(i = -SEARCH_RADIUS; i <= SEARCH_RADIUS; i++) {
		for(j = -SEARCH_RADIUS; j <= SEARCH_RADIUS; j++) {
			for(k = 0; k < enemy_count; k++) {
				if(is_out_of_bounds(player->y + i, player->x + j))
					continue;

				if(game_place[player->y + i][player->x + j] == enemy[k]) {
					game_place[player->y +i][player->x + j] = SPACE;
					if(fight(max_y, max_x, player, who_enemy(enemy[k])))
						return 1;
				}
			}
		}
	}

	return 0;
}
