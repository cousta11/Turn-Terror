#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fight.h"
#include "screen.h"

int healing(int mod, int *hp, int *max_hp)
{
	if(mod > 0) {
		if(*hp == *max_hp)
			return 0;
		else if(*hp + mod > *max_hp)
			*hp = *max_hp;
		else
			*hp += mod;
	} else if(mod < 0) {
		if(*hp + mod <= 0)
			*hp = 0;
		else
		 *hp += mod;
	}
	return 1;
}
char *hp_str(char str[], int str_len, int hp, int max_hp, enum type_win w)
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
	if(w == sp_player)
		snprintf(buf, buf_len, "] SP: %d/%d [", hp, max_hp);
	else
		snprintf(buf, buf_len, "] HP: %d/%d [", hp, max_hp);
	buf_len = strlen(buf);
	for(i = 0; i < buf_len; i++)
		str[str_len/2 - buf_len/2 + i] = buf[i];
	return str;
}
void event_hp(int y, enum type_win w, int hp, int max_hp, int str_len, int col,
		win_t **window)
{
	char *str = malloc(str_len);
	hp_str(str, str_len, hp, max_hp, w);
	hp_display(y, 1, strlen(str), str, col, w, window);
	free(str);
}
void event(int max_y, int max_x, enum type_win w, win_t **window, gamer *player,
		struct enemy *enemy)
{
	switch(w) {
		case start: break;
		case sp_player:
			event_hp(max_y - 2 , w, player->sp, player->max_sp, max_x, 5, window);
			break;
		case hp_player:
			event_hp(max_y - 1 , w, player->hp, player->max_hp, max_x, 4, window);
			break;
		case hp_enemy:
			event_hp(1, w, enemy->hp, enemy->max_hp, max_x, 2, window);
			break;
		case end: break;
	}
}
