#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fight.h"
#include "screen.h"

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
void event(int max_y, int max_x, enum type_win w, win **window, gamer *player,
		struct enemy *enemy)
{
	int str_len = max_x;
	char *str = malloc(str_len);
	switch(w) {
		case start: break;
		case panel: break;
		case menu: break;
		case place: break;
		case end: break;
		case hp_player:
			hp_str(str, str_len, player->hp, player->max_hp);
			hp_display(max_y - 1, 1, strlen(str), str, 4, hp_player, window);
			break;
		case hp_enemy:
			hp_str(str, str_len, enemy->hp, enemy->max_hp);
			hp_display(1, 1, strlen(str), str, 2, hp_enemy, window);
			break;
	}
	free(str);
}
