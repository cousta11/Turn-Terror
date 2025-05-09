#include "../include/sup_func.h"
#include "../include/fight.h"

int start_fight(const int y, const int x, int *enemy_y, int *enemy_x,
		const int game_place[SIZE][SIZE])
{
	int ENEMIES, i, j, k;
	for(i = -2; i < 3; i++) {
		for(j = -2; j < 3; j++) {
			for(k = 0; k < SIZE_ENEMIES; k++) {
				if(game_place[y + i][x + j] == enemies[k]) {
					*enemy_y = y + i;
					*enemy_x = x + j;
					return 1;
				}
			}
		}
	}
	return 0;
}
int battle_line(int y, int x, int lenght, int hit_zone)
{
	int i, hx = rand_to(x + 1, x + lenght - hit_zone - 1);
	attrset(COLOR_PAIR(3));
	mvaddch(y, x, '[');
	for(i = lenght - 2; i > 0; i--) {
		addch('=');
	}
	addch(']');
	attrset(COLOR_PAIR(4));
	move(y, hx);
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
void hit(int max_y, int max_x, int player_hp, int enemy_hp, int *mob1, int *mob2)
{
	int i, lenght = max_x/2;
	hp_display(max_y, max_x, player_hp, enemy_hp);
	for(i = 1; i < lenght - 2; i++) {
		attrset(COLOR_PAIR(3));
		mvaddch(max_y/2 + 4/2, max_x/2 - max_x/4 + i, '=');
		mvaddch(max_y/2 + 4/2, max_x/2 - max_x/4 + 1 + i, WALL);
		if(getch() == ' ') {
			*mob1 -= 1;
			break;
		}
		refresh();
	}
	if(i == lenght - 2)
		*mob2 -= 1;
}
int fight(int max_y, int max_x, int enemy_y, int enemy_x,
		gamer *player, int game_place[SIZE][SIZE])
{
	int hit_zone = max_x/2/10;
	int enemy_hp = 15;
	clear();
	attrset(COLOR_PAIR(2));
	mvaddch(max_y/3, max_x/2 - 1, game_place[enemy_y][enemy_x]);
	timeout(100);
	while(enemy_hp > 0 && player->hp > 0) {
		battle_line(max_y/2 + 4/2, max_x/2 - max_x/4, max_x/2, hit_zone);
		hit(max_y, max_x, player->hp, enemy_hp, &enemy_hp, &player->hp);
		battle_line(max_y/2 + 4/2, max_x/2 - max_x/4, max_x/2, hit_zone);
		hit(max_y, max_x, player->hp, enemy_hp, &player->hp, &enemy_hp);
		refresh();
	}
	if(player->hp < 1) {
		timeout(-1);
		return 0;
	}
	game_place[enemy_y][enemy_x] = SPACE;
	timeout(-1);
	return 1;
}
