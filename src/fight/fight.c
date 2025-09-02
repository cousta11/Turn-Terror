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

#define LEN_STORY_STEP 3
#define ZERO -1
#define ATTACK 0
#define DEFENSE 1
#define PARRY 2
#define AMOUNT_ACT 3

int step_player(int max_y, int max_x)
{
	int c;
	menu_t *menu = create_menu((max_y/2 - AMOUNT_ACT/2), 0, 5, max_x/3,
			"Attack", "Defense", "Parry", NULL);
	mrefresh(menu);
	while((c = getch()) != EOF) {
		switch(c) {
			case DOWN_K:
				menu_driver(menu_menu(menu), REQ_DOWN_ITEM);
				break;
			case UP_K:
				menu_driver(menu_menu(menu), REQ_UP_ITEM);
				break;
			case INTERACTION_K:
				return item_index(current_item(menu_menu(menu)));
				break;
		}
		mrefresh(menu);
	}
	del_menu(&menu);
	return PARRY;
}
int step_enemy(int steps[LEN_STORY_STEP])
{
	return ATTACK;
}
enum type_win attack(int step[2], gamer *player, struct enemy *enemy)
{
	int tmp;
	switch(step[0]) {
		case ATTACK:
			tmp = player->dmg - enemy->dmg;
			if(tmp > 0) {
				enemy->hp -= tmp;
				if(enemy->hp < 0)
					enemy->hp = 0;
				return hp_enemy;
			}
			if(tmp < 0){
				player->hp -= tmp;
				if(player->hp < 0)
					player->hp = 0;
				return hp_player;
			}
			break;
		case DEFENSE:
			tmp = player->dmg - enemy->armor;
			if(tmp > 0) {
				enemy->hp -= tmp;
				if(enemy->hp < 0)
					enemy->hp = 0;
				return hp_enemy;
			}
			break;
	}
	return end;
}
enum type_win defense(int step[2], gamer *player, struct enemy *enemy)
{
	int tmp;
	if(step[0] == ATTACK) {
		tmp = enemy->dmg - player->armor;
		if(tmp > 0) {
			player->hp -= tmp;
			if(player->hp < 0)
				player->hp = 0;
			return hp_player;
		}
	}
	return end;
}
enum type_win result_step(int step[2], gamer *player, struct enemy *enemy)
{
	if(step[0] == PARRY || step[1] == PARRY) return end;
	if(step[1] == ATTACK) return attack(step, player, enemy);
	if(step[1] == DEFENSE) return defense(step, player, enemy);
	return end;
}
int fight(int max_y, int max_x, gamer *player, struct enemy *enemy)
{
	enum type_win event_type;
	win_t *window = NULL;
	int steps[LEN_STORY_STEP] = {ZERO, ZERO, ZERO}, step[2] = {ZERO, ZERO};
	clear();
	wattron(stdscr, COLOR_PAIR(2));
	mvaddstr(0, max_x/2 - strlen(enemy->name)/2, enemy->name);
	for(event_type = start; event_type < end; event_type++)
		event(max_y, max_x, event_type, &window, player, enemy);
	while(player->hp > 0 && enemy->hp > 0) {
		step[0] = step_enemy(steps);
		step[1] = step_player(max_y, max_x);
		event_type = result_step(step, player, enemy);
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
