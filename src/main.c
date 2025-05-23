#include "../include/sup_func.h"
#include "../include/dungeon.h"
#include "../include/screen.h"
#include "../include/fight.h"

void winner(int max_y, int max_x, gamer *player, int game_place[SIZE][SIZE])
{
	clear();
	attrset(COLOR_PAIR(4));
	mvaddstr(max_y/2, max_x/2 - 12/2, "You winner!\n");
	mvaddstr(max_y/2 + 1, max_x/2 - 24/2, "quit[q] restart[r/any]\n");
	if(getch() == 'q') {
		endwin();
	} else {
		preparing_the_dungeon(max_y, max_x, game_place, player);
		player->hp = MAX_HP;
	}
}
int finish(int x, int y, int game_place[SIZE][SIZE])
{
	int i, j;
	for(i = -1; i < 2; i++) {
		for(j = -1; j < 2; j++) {
			if(game_place[x + i][y + j] == FORESTER)
				return 1;
		}
	}
	return 0;
}

int main()
{
	int max_y, max_x, work_bw, i = 0, enemy_y, enemy_x;
	int game_place[SIZE][SIZE];
	int combat;
	gamer player;
	/* terminal preparation */
    initscr();
    getmaxyx(stdscr, max_y, max_x);
	if(max_y < 24 || max_x < 80) {
		endwin();
		fprintf(stderr, "Error: terminal must be >= 24x80\n");
		return 1;
	}
	work_bw = !has_colors();
	if(!work_bw) {
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(4, COLOR_GREEN, COLOR_BLACK);
		attrset(COLOR_PAIR(1));
	}
	cbreak();
    noecho();
    curs_set(0);
	srand(time(NULL));
	player.hp = MAX_HP;
	preparing_the_dungeon(max_y, max_x, game_place, &player);

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
		if(start_fight(player.y, player.x, &enemy_y, &enemy_x, game_place)) {
			combat = fight(max_y, max_x, enemy_y, enemy_x, &player, game_place);
			if(!combat) {
				clear();
				attrset(COLOR_PAIR(2));
				mvaddstr(max_y/2, max_x/2 - 10/2, "You lose!\n");
				mvaddstr(max_y/2 + 1, max_x/2 - 24/2, "quit[q] restart[r/any]\n");
				if(getch() == 'q') {
					endwin();
					return 0;
				} else {
					preparing_the_dungeon(max_y, max_x, game_place, &player);
					player.hp = MAX_HP;
				}
			} else {
    			getmaxyx(stdscr, max_y, max_x);
				scr_replay(game_place, &player, max_y, max_x);
			}
		}
		if(i == 10) {
    		getmaxyx(stdscr, max_y, max_x);
			scr_replay(game_place, &player, max_y, max_x);
			i = 0;
		} else i++;
		if(finish(player.y, player.x, game_place))
			winner(max_y, max_x, &player, game_place);
		refresh();
	}

	endwin();
	return 0;
}
