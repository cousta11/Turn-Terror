#include "../include/sup_func.h"
#include "../include/dangeon.h"

void mvplayer(int mod_y, int mod_x, int arr[SIZE][SIZE], struct gamer *player)
{
	int y = player->y;
	int x = player->x;
	y += mod_y;
	x += mod_x;
	if(y > SIZE - 1 || y < 0)
		return;
	if(x > SIZE - 1 || x < 0)
		return;
	if(arr[y][x] != SPACE)
		return;
	mvaddch(player->y, player->x, SPACE);
	player->y += mod_y;
	player->x += mod_x;
	mvaddch(player->y, player->x, CHAR);
	return;
}

int main(int argc, char *argv[])
{
	int max_y, max_x, work_bw;
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
	work_bw = !has_colors();
	if(!work_bw) {
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
	}
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
	mvaddch(player.y, player.x, CHAR);
	while(1) {	
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
		refresh();
	}

	endwin();
	return 0;
}
