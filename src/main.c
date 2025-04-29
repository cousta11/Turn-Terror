#include "../include/sup_func.h"
#include "../include/dangeon.h"

void mvplayer(int mod_y, int mod_x, int arr[SIZE][SIZE], struct gamer *player)
{
	int y = player->y + mod_y;
	int x = player->x + mod_x;
    if(out_the_barrier(y, x) || arr[y][x] != SPACE)
        return;

	mvaddch(player->scr_y, player->scr_x, SPACE);
	player->y += mod_y;
	player->x += mod_x;
	player->scr_y += mod_y;
	player->scr_x += mod_x;
	mvaddch(player->scr_y, player->scr_x, CHAR);
	return;
}
void scr_replay(int game_place[SIZE][SIZE], gamer *player, int max_y, int max_x)
{
	int y = player->y - (max_y/2);
	int x = player->x - (max_x/2), i, j;
	if (y < 0) y = 0;
    if (x < 0) x = 0;
    if (y + max_y >= SIZE) y = SIZE - max_y;
    if (x + max_x >= SIZE) x = SIZE - max_x;
	clear();
	for(i = 0; i < max_y; i++) {
		for(j = 0; j < max_x; j++) {
			mvaddch(i, j, game_place[y + i][x + j]);
		}
	}
    player->scr_y = player->y - y;
    player->scr_x = player->x - x;
    if (player->scr_y >= 0 && player->scr_y < max_y &&
        player->scr_x >= 0 && player->scr_x < max_x) {
        mvaddch(player->scr_y, player->scr_x, CHAR);
    }
}

int main(int argc, char *argv[])
{
	int max_y, max_x/*, work_bw*/;
	int i, j;
	gamer player;
	int game_place[SIZE][SIZE];
	/* terminal preparation */
    initscr();
    getmaxyx(stdscr, max_y, max_x);
	if(max_y < 24 || max_x < 80) {
		endwin();
		printf("Error: terminal must be >= 24x80\n", stderr);
		return 1;
	}
	/*work_bw = !has_colors();
	if(!work_bw) {
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
	}*/
	cbreak();
    noecho();
    curs_set(0);
	srand(time(NULL));

	/* tmporarily */
	player.lvl = 1;
	player.max_hp = player.lvl * 2;
	player.max_mp = player.lvl * 4;
	/* end tmporarily */
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			game_place[i][j] = WALL;
	dangeon_genereted(&player.y, &player.x, game_place);
	scr_replay(game_place, &player, max_y, max_x);
	for(i = 0; i != -1; i++){	
		switch(getch()) {
			case 'q':
				endwin();
				return 0;
				break;
			case 'h':
				mvplayer(0, -1, game_place, &player);
				break;
			case 'j':
				mvplayer(1, 0, game_place, &player);
				break;
			case 'k':
				mvplayer(-1, 0, game_place, &player);
				break;
			case 'l':
				mvplayer(0, 1, game_place, &player);
				break;
		}
		if(i == 10) {
			scr_replay(game_place, &player, max_y, max_x);
			i = 0;
		}
		refresh();
	}

	endwin();
	return 0;
}
