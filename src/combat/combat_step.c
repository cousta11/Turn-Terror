#include <ncurses.h>
#include <menu.h>
#include <string.h>

#include "combat_event.h"
#include "control.h"
#include "menu_api.h"
#include "random.h"

#define TIME_NAPMS 30
#define LEN_STORY_STEP 3
#define ZERO -1
#define ATTACK 0
#define DEFENSE 1
#define PARRY 2
#define AMOUNT_ACT 3
#define SP_ATTACK 5
#define LEN_STR_ACT 29

struct act {
	char attack[LEN_STR_ACT];
	char defense[LEN_STR_ACT];
	char parry[LEN_STR_ACT];
};

static void str_act(char *str, const char *source, const int value, const int max_len)
{
	int len, len_str, i;
	char val_str[8];

	snprintf(val_str, sizeof(val_str), "SP: %d", value);

	strcpy(str, source);

	len = strlen(val_str);
	len_str = strlen(str);

	for(i = 0; i + len_str < max_len; i++)
		str[len_str + i] = ' ';

	for(i = 0; i <= len; i++)
		str[max_len - i] = val_str[len - i];
}
static menu_t *step_menu(const int max_y, const int max_x, struct act *str,
		const int val_attack, const int val_defense, const int val_parry)
{
	menu_t *menu = NULL;
	int len = sizeof(char)*max_x/3 - 4 + 1;

	str_act(str->attack, "Attack", val_attack, len - 1);
	str_act(str->defense, "Defense", val_defense, len - 1);
	str_act(str->parry, "Parry", val_parry, len - 1);

	menu = create_menu((max_y/2 - AMOUNT_ACT/2), max_x/2 - max_x/3/2,
			5, max_x/3, str->attack, str->defense, str->parry, NULL);

	return menu;
}
static int step_control(menu_t *menu)
{
	int c;

	for(;;) {
		mrefresh(menu);

		switch(c = getch()) {
			case DOWN_K:
				menu_driver(menu->menu, REQ_DOWN_ITEM);
				break;
			case UP_K:
				menu_driver(menu->menu, REQ_UP_ITEM);
				break;
			case INTERACTION_K:
				return item_index(current_item(menu->menu));
				break;
		}
	}
}
static int step_player(const int max_y, const int max_x, const player_t *player)
{
	int res;
	struct act str;

	menu_t *menu = step_menu(max_y, max_x, &str,
			(SP_ATTACK - player->mod_sp) * -1, 1, 0);

	refresh();

	res = step_control(menu);

	del_menu(&menu);
	return res;
}
static void len_ch(const int y, const int x, const int len_x, const char ch, const int col)
{
	attrset(COLOR_PAIR(col));
	mvhline(y, x, ch, len_x + 1);
}
static void create_hb(const int y, const int x, const int len_x,
		const int hit_x, const int hit_len)
{
	len_ch(y, x, len_x, '=', 3);
	mvaddch(y, x - 1, '[');
	mvaddch(y, x + len_x + 1, ']');
	len_ch(y, hit_x, hit_len, '=', 4);
	attrset(COLOR_PAIR(3));
}
static int hit_bar(const int max_y, const int max_x)
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
		napms(TIME_NAPMS);
		current_pos++;
	}
	nodelay(stdscr, FALSE);
	len_ch(y, x - 1, len_x + 3, ' ', 1);
	return (current_pos >= hit_x && current_pos <= hit_x + hit_len);
}
static int attack(const int res, player_t *player, enemy_t *enemy)
{
	if(!res) return end;
	change_of_state(player->dmg * -1, &(enemy->hp), &(enemy->max_hp));
	return hp_enemy;
}
static int defense(const int res, player_t *player, enemy_t *enemy)
{
	if(res) return end;
	change_of_state(enemy->dmg * -1, &(player->hp), &(player->max_hp));
	return hp_player;
}
static int parry(const int res, player_t *player, enemy_t *enemy)
{
	if(res) return end;
	change_of_state(enemy->dmg * -1, &(player->hp), &(player->max_hp));
	return end;
}
static void is_can_act(const int max_y, const int max_x, int *act, player_t *player)
{
	int i = 1;
	while(i) {
		*act = step_player(max_y, max_x, player);
		switch(*act) {
			case ATTACK:
				if(!(player->sp - SP_ATTACK + player->mod_sp >= 0)) break;
				change_of_state(player->mod_sp - SP_ATTACK,
						&(player->sp), &(player->max_sp));
				i = player->mod_sp = 0;
				break;
			default:
				if(*act == DEFENSE)
					change_of_state(1, &(player->sp), &(player->max_sp));
				if(*act == PARRY)
					player->mod_sp = 2;
				i = 0;
		}
	}
}

enum type_win step(const int max_y, const int max_x, player_t *player,
		enemy_t *enemy)
{
	int act, res;
	is_can_act(max_y, max_x, &act, player);
	res = hit_bar(max_y, max_x);
	switch(act) {
		case ATTACK: return attack(res, player, enemy); break;
		case DEFENSE: return defense(res, player, enemy); break;
		case PARRY: return parry(res, player, enemy); break;
	}
	return end;
}
