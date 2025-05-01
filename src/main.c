#include "../include/sup_func.h"
#include "../include/dangeon.h"
#include "../include/screen.h"

int main()
{
	int max_y, max_x, work_bw;
	int i;
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
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
		attrset(COLOR_PAIR(1));
	}
	cbreak();
    noecho();
    curs_set(0);
	srand(time(NULL));
	/* tmporarily */
	player.lvl = 1;
	player.max_hp = player.lvl * 2;
	player.max_mp = player.lvl * 4;
	player.hp = player.max_hp;
	player.mp = player.max_mp;
	/* end tmporarily */
	preparing_the_dungeon(max_y, max_x, game_place, &player);
	i = 0;
	while(1){	
		switch(getch()) {
			case 'q':
				endwin();
				return 0;
				break;
			case 'r':
				preparing_the_dungeon(max_y, max_x, game_place, &player);
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
		} else i++;
		refresh();
	}

	endwin();
	return 0;
}
