#include "../include/sup_func.h"
#include "../include/dangeon.h"

void mvplayer(int mod_y, int mod_x, int arr[SIZE][SIZE], struct gamer *player)
{
	int y = player->y + mod_y;
	int x = player->x + mod_x;
    if(out_the_barrier(y, x) || arr[y][x] != SPACE)
        return;
	attrset(COLOR_PAIR(1));
	mvaddch(player->scr_y, player->scr_x, SPACE);
	player->y += mod_y;
	player->x += mod_x;
	player->scr_y += mod_y;
	player->scr_x += mod_x;
	mvaddch(player->scr_y, player->scr_x, CHAR);
	return;
}
void atmvaddch(int y, int x, int c, int cl_pair)
{
	attrset(COLOR_PAIR(cl_pair));
	mvaddch(y, x, c);
}
void map_replay(int y, int x, int max_y, int max_x, int game_place[SIZE][SIZE])
{
	int i, j;
	for(i = 0; i < max_y; i++) {
		for(j = 0; j < max_x; j++) {
			switch(game_place[y + i][x + j]) {
				case SPACE: atmvaddch(i, j, SPACE, 1); break;
				case WALL: atmvaddch(i, j, WALL, 1); break;
				case FORESTER: atmvaddch(i, j, FORESTER, 3); break;
				case 'T': atmvaddch(i, j, 'T', 2); break;
			}
		}
	}
}
void scr_replay(int game_place[SIZE][SIZE], gamer *player, int max_y, int max_x)
{
	int y = player->y - (max_y/2);
	int x = player->x - (max_x/2);
	if (y < 0) y = 0;
    if (x < 0) x = 0;
    if (y + max_y >= SIZE) y = SIZE - max_y;
    if (x + max_x >= SIZE) x = SIZE - max_x;
	clear();
	map_replay(y, x, max_y, max_x, game_place);
	attrset(COLOR_PAIR(1));
    player->scr_y = player->y - y;
    player->scr_x = player->x - x;
    if (player->scr_y >= 0 && player->scr_y < max_y &&
        player->scr_x >= 0 && player->scr_x < max_x) {
        mvaddch(player->scr_y, player->scr_x, CHAR);
    }
}
