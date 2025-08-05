#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <unistd.h>
#include <string.h>

#include "../include/main.h"
#include "../include/fight.h"
#include "../include/screen.h"
#include "../include/dungeon.h"

char *hp_str(char *str, int hp)
{
	snprintf(str, sizeof(str), "HP: %d", hp);
	return str;
}

int fight(int max_y, int max_x, gamer *player, int enemy)
{
	char str[7];
	win *window = NULL;
	clear();
	hp_str(str, player->hp);
	hp_display(max_y - 1, 0, 1, strlen(str), str, 4, &window);
	hp_str(str, player->hp + 10);
	hp_display(0, max_x - strlen(str), 1, strlen(str), str, 2, &window);
	getch();
	free_display(window);
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
					if(fight(max_y, max_x, player, enemy[k]))
						return 1;
				}
			}
		}
	}
	scr_replay(max_y, max_x, player, game_place);
	return 0;
}
