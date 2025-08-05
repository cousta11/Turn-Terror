#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../include/main.h"
#include "../include/fight.h"
#include "../include/screen.h"
#include "../include/dungeon.h"

struct enemy {
	int hp;
};

int healing(int mod, gamer *player)
{
	if(player->hp == player->max_hp)
		return 0;
	if(player->hp + mod > player->max_hp)
		player->hp = player->max_hp;
	else
		player->hp += mod;
	return 1;
}
char *hp_str(char *str, int hp)
{
	snprintf(str, sizeof(str), " HP: %d ", hp);
	return str;
}

struct enemy *who_enemy(char c)
{
	struct enemy *enemy = malloc(sizeof(struct enemy));
	enemy->hp = 0;
	switch(c) {
		case 'T': enemy->hp = 15; break;
		case 'O': enemy->hp = 8; break;
		case 'G': enemy->hp = 5; break;
	}
	return enemy;
}

int fight(int max_y, int max_x, gamer *player, struct enemy *enemy)
{
	char *str = malloc(max_x + 1);
	win *window = NULL;
	clear();
	while(player->hp > 0 && enemy->hp > 0) {
		hp_str(str, player->hp);
		hp_display(max_y - 1, 0, 1, strlen(str), str, 4, &window);
		hp_str(str, enemy->hp);
		hp_display(0, max_x - strlen(str), 1, strlen(str), str, 2, &window);
		switch(getch()) {
			case 'q': enemy->hp = 0; break;
			case 'j': enemy->hp--; break;
			case 'l': player->hp--; break;
		}
	}
	free_display(window);
	free(enemy);
	free(str);
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
