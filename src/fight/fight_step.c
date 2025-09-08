#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>

#include "main.h"
#include "fight.h"
#include "fight_event.h"
#include "control.h"
#include "menu_api.h"
#include "random_range.h"

#define LEN_STORY_STEP 3
#define ZERO -1
#define ATTACK 0
#define DEFENSE 1
#define PARRY 2
#define AMOUNT_ACT 3

int step_player(int max_y, int max_x)
{
	int c, res;
	menu_t *menu = create_menu((max_y/2 - AMOUNT_ACT/2), max_x/2 - max_x/3/2,
			5, max_x/3, "Attack", "Defense", "Parry", NULL);
	refresh();
	for(;;) {
		mrefresh(menu);
		switch(c = getch()) {
			case DOWN_K:
				menu_driver(menu_menu(menu), REQ_DOWN_ITEM);
				break;
			case UP_K:
				menu_driver(menu_menu(menu), REQ_UP_ITEM);
				break;
			case INTERACTION_K:
				res = item_index(current_item(menu_menu(menu)));
				goto cleanup;
				break;
		}
	}
cleanup:
	del_menu(&menu);
	return res;
}
void len_ch(int y, int x, int len_x, char ch, int col)
{
	attrset(COLOR_PAIR(col));
	mvhline(y, x, ch, len_x + 1);
}
void create_hb(int y, int x, int len_x, int hit_x, int hit_len)
{
	len_ch(y, x, len_x, '=', 3);
	mvaddch(y, x - 1, '[');
	mvaddch(y, x + len_x + 1, ']');
	len_ch(y, hit_x, hit_len, '=', 4);
	attrset(COLOR_PAIR(3));
}
int hit_bar(int max_y, int max_x)
{
	int y = max_y/2, x = max_x/4, len_x = max_x/2, current_pos = x;
	int hit_x = random_range(x, len_x), hit_len = len_x/5;
	create_hb(y, x, len_x, hit_x, hit_len);
	nodelay(stdscr, TRUE);
	while(current_pos <= x + len_x) {
		mvaddch(y, current_pos, '#');
		refresh();
		if(current_pos > x)
			mvaddch(y, current_pos - 1, '=');
		if(getch() != ERR)
			break;
		napms(100);
		current_pos++;
	}
	nodelay(stdscr, FALSE);
	len_ch(y, x - 1, len_x + 3, ' ', 1);
	return (current_pos >= hit_x && current_pos <= hit_x + hit_len);
}
int attack(int res, gamer *player, struct enemy *enemy)
{
	if(!res) return end;
	healing(player->dmg * -1, &(enemy->hp), &(enemy->max_hp));
	return hp_enemy;
}
int defense(int res, gamer *player, struct enemy *enemy)
{
	if(res) return end;
	healing(enemy->dmg * -1, &(player->hp), &(player->max_hp));
	return hp_player;
}
int parry(int res, gamer *player, struct enemy *enemy)
{
	if(res) return end;
	healing(enemy->dmg * -1, &(player->hp), &(player->max_hp));
	return end;
}
enum type_win step(int max_y, int max_x, gamer *player, struct enemy *enemy)
{
	int act, res, i = 1;
	while(i) {
		act = step_player(max_y, max_x);
		switch(act) {
			case ATTACK:
				if(!(player->sp - 5 + player->mod_sp >= 0)) break;
				healing(-5, &(player->sp), &(player->max_sp));
				i = 0; player->mod_sp = 0;
				break;
			default:
				if(act == DEFENSE) healing(1, &(player->sp), &(player->max_sp));
				if(act == PARRY) player->mod_sp = 1;
				i = 0;
		}
	}
	res = hit_bar(max_y, max_x);
	switch(act) {
		case ATTACK: return attack(res, player, enemy); break;
		case DEFENSE: return defense(res, player, enemy); break;
		case PARRY: return parry(res, player, enemy); break;
	}
	return end;
}
