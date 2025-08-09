#include <menu.h>
#include <stdlib.h>
#include <string.h>

#include "../include/screen.h"
#include "../include/dungeon.h"

struct enemy {
	char *name;
	int hp, max_hp;
};

int healing(int mod, int *hp, int *max_hp)
{
	if(*hp == *max_hp)
		return 0;
	if(*hp + mod > *max_hp)
		*hp = *max_hp;
	else
		*hp += mod;
	return 1;
}
char *hp_str(char str[], int str_len, int hp, int max_hp)
{
	char buf[32];
	int i, buf_len = sizeof(buf);
	int mhp = (str_len - 1) - ((max_hp - hp)*((str_len - 2)/max_hp));
	str[str_len] = '\0';
	str[0] = '[';
	str[str_len - 1] = ']';
	for(i = 1; i < str_len - 1; i++)
		str[i] = '=';
	for(i = mhp; i < str_len - 1 || i > str_len - 1; i++)
		str[i] = ' ';
	snprintf(buf, buf_len, "] HP: %d/%d [", hp, max_hp);
	buf_len = strlen(buf);
	for(i = 0; i < buf_len; i++)
		str[str_len/2 - buf_len/2 + i] = buf[i];
	return str;
}
struct enemy *who_enemy(char c)
{
	struct enemy *enemy = malloc(sizeof(struct enemy));
	enemy->hp = 0;
	switch(c) {
		case 'T':
			enemy->max_hp = enemy->hp = 15;
			enemy->name = "Troll";
			break;
		case 'O':
			enemy->max_hp = enemy->hp = 8;
			enemy->name = "Orc";
			break;
		case 'G':
			enemy->max_hp = enemy->hp = 5;
			enemy->name = "Goblin";
			break;
	}
	return enemy;
}
enum type_win *fight_control(gamer *player, struct enemy *enemy)
{
	enum type_win *res = malloc(sizeof(enum type_win));
	*res = end;
	switch(getch()) {
		case 'q': enemy->hp = 0; break;
		case 'j': enemy->hp--; *res = hp_enemy; break;
		case 'l': player->hp--; *res = hp_player; break;
	}
	return res;
}
int fight(int max_y, int max_x, gamer *player, struct enemy *enemy)
{
	char *str = malloc(max_x);
	int str_len = max_x;
	win *window = NULL;
	clear();
	mvaddstr(0, 0, enemy->name);
	while(player->hp > 0 && enemy->hp > 0) {
		hp_str(str, str_len, player->hp, player->max_hp);
		hp_display(max_y - 1, 1, strlen(str), str, 4, hp_player, &window);
		hp_str(str, str_len, enemy->hp, enemy->max_hp);
		hp_display(1, 1, strlen(str), str, 2, hp_enemy, &window);
		free(fight_control(player, enemy));
	}
	free(enemy);
	free(str);
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
