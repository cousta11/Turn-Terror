#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <menu.h>

#include "main.h"
#include "menu_api.h"
#include "control.h"
#include "fight_event.h"
#include "dungeon.h"
#include "who_enemy.h"

enum act {attack, defense, parry, counterattak};
typedef struct step {
	enum act player, enemy;
} step_t;

enum type_win step_logic(step_t *step, gamer *player, struct enemy *enemy)
{
	int tmp;
	switch(step->player) {
		case attack:
			if(step->enemy == attack) {
				tmp = player->dmg - enemy->dmg;
				if(tmp > 0) enemy->hp -= tmp; return hp_enemy;
				if(tmp < 0)player->hp -= tmp; return hp_player;
			}
			break;
		case defense:
			if(step->enemy == attack) {
				tmp = enemy->dmg - player->armor;
				if(tmp > 0) player->hp -= tmp; return hp_player;
			}
			break;
		case parry: break;
		case counterattak: break;
	}
	return end;
}
enum act step_enemy()
{
	return attack;
}
enum act step_player(menu_t *menu)
{
	int c;
	ITEM *cur = NULL;
	while((c = getch()) != QUIT_K) {
		switch(c) {
			case DOWN_K:
				menu_driver(menu_menu(menu), REQ_DOWN_ITEM);
				break;
			case UP_K:
				menu_driver(menu_menu(menu), REQ_UP_ITEM);
				break;
			case INTERACTION_K: 
				cur = current_item(menu_menu(menu));
				break;
		}
		if(cur) break;
		mrefresh(menu);
	}
	return (enum act)item_index(cur);
}
enum type_win fight_control(int max_y, int max_x, gamer *player,
		struct enemy *enemy)
{
	enum type_win res = end;
	menu_t *menu = create_menu(max_y/4, 0, max_y/4, max_x/4,
			"attack", "defense", "parry", NULL);
	step_t step;
	step.enemy = step_enemy();
	step.player = step_player(menu);
	res = step_logic(&step, player, enemy);
	del_menu(&menu);
	return res;
}
int fight(int max_y, int max_x, gamer *player, struct enemy *enemy)
{
	enum type_win step;
	win_t *window = NULL;
	clear();
	refresh();
	wattron(stdscr, COLOR_PAIR(2));
	mvaddstr(0, max_x/2 - strlen(enemy->name)/2, enemy->name);
	for(step = start; step < end; step++)
		event(max_y, max_x, step, &window, player, enemy);
	while(player->hp > 0 && enemy->hp > 0) {
		step = fight_control(max_y, max_x, player, enemy);
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
