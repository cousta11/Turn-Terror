#include "main.h"
#include "fight.h"
#include "rand_to.h"
#include "screen.h"

#define DEAD_ZONE 6

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
int battle_line(int y, int x, int lenght, int hit_zone, int *hx)
{
	int i;
	*hx = rand_to(x + DEAD_ZONE, x + lenght - hit_zone - 1);
	attrset(COLOR_PAIR(3));
	mvaddch(y, x, '[');
	for(i = lenght - 2; i > 0; i--) {
		addch('=');
	}
	addch(']');
	attrset(COLOR_PAIR(4));
	move(y, *hx);
	for(i = 0; i < hit_zone; i++) {
		addch('-');
	}
	return 1;
}
void hp_display(int max_y, int max_x, int player_hp, int enemy_hp)
{
	attrset(COLOR_PAIR(4));
	mvprintw(max_y/2 + 4/2 + 1, max_x/2 - max_x/4, "HP: %d", player_hp);
	addstr("   ");
	attrset(COLOR_PAIR(2));
	mvprintw(max_y/2 + 4/2 - 1, max_x/2 - max_x/4, "HP: %d", enemy_hp);
	addstr("   ");
}
void hit(int max_y, int max_x, int *player_hp, int *enemy_hp, int *hx)
{
	int i, lenght = max_x/2, x;
	hp_display(max_y, max_x, *player_hp, *enemy_hp);
	for(i = 1; i < lenght - 2; i++) {
		attrset(COLOR_PAIR(3));
		mvaddch(max_y/2 + 4/2, max_x/2 - max_x/4 + i, '=');
		mvaddch(max_y/2 + 4/2, max_x/2 - max_x/4 + 1 + i, WALL);
		x = getcurx(stdscr);
		if(getch() == ' ') {
			if(x >= *hx && x <= *hx + lenght/10) {
				*enemy_hp -= 1;
				break;
			} else {
				*player_hp -= 1;
				break;
			}
		}
		if(x >= max_x*0.75 - 1)
			*player_hp -= 1;
		if(*player_hp <= 0)
			break;
		refresh();
	}
}
int fight(int max_y, int max_x, int enemy_y, int enemy_x,
		gamer *player, int game_place[SIZE][SIZE])
{
	int hit_zone = max_x/2/10, hx, enemy_hp = 0;
	switch(game_place[enemy_y][enemy_x]) {
		case 'G': enemy_hp = 5; break;
		case 'O': enemy_hp = 8; break;
		case 'T': enemy_hp = 15; break;
		case 'H':
			if((player->hp + 1) <= START_MAX_HP)
				player->hp++;
			else
				return 0;
			break;
	}
	clear();
	attrset(COLOR_PAIR(2));
	mvaddch(max_y/3, max_x/2 - 1, game_place[enemy_y][enemy_x]);
	timeout(60);
	while(enemy_hp > 0 && player->hp > 0) {
		battle_line(max_y/2 + 4/2, max_x/2 - max_x/4, max_x/2, hit_zone, &hx);
		hit(max_y, max_x, &player->hp, &enemy_hp, &hx);
		refresh();
	}
	game_place[enemy_y][enemy_x] = SPACE;
	timeout(-1);
	if(player->hp < 1)
		return 1;
	return 0;
}
int start_fight(int max_y, int max_x, gamer *player, int game_place[SIZE][SIZE])
{
	int enemies[] = ENEMIES, i, j, k, enemy_y, enemy_x;
	int size_enemies = sizeof(enemies)/sizeof(int);
	int y = player->y, x = player->x;
	for(i = -2; i < 3; i++) {
		for(j = -2; j < 3; j++) {
        	if(y + i < 0 || y + i >= SIZE || x + j < 0 || x + j >= SIZE)
        	    continue;
			for(k = 0; k < size_enemies; k++) {
				if(game_place[y + i][x + j] == enemies[k]) {
					enemy_y = y + i;
					enemy_x = x + j;
					if(fight(max_y, max_x, enemy_y, enemy_x, player, game_place))
						return 1;
				}
			}
		}
	}
	scr_replay(max_y, max_x, player, game_place);
	return 0;
}
