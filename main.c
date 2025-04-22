#include "main.h"

void mvplayer(const int mod_y, const int mod_x,
		const int max_y, const int max_x, struct gamer *player)
{
	int y = player->y;
	int x = player->x;
	if(y + mod_y > max_y || y + mod_y < 0)
		return;
	if(x + mod_x > max_x || x + mod_x < 0)
		return;
	player->y += mod_y;
	player->x += mod_x;
	return;
}

int main(int argc, char *argv[])
{
	int max_y, max_x, work_bw;
	mobs *enemies = NULL;
	gamer player;
	/* terminal preparation */
    initscr();
    getmaxyx(stdscr, max_y, max_x);
	if(max_y < 24 || max_x < 80) {
		fprintf(stderr, "Error: terminal must be >= 24x80\n");
		endwin();
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

	player.y = max_y-- / 2;
	player.x = max_x-- / 2;
	/* tmporarily */
	player.lvl = 1;
	player.max_hp = player.lvl * 2;
	player.max_mp = player.lvl * 4;
	/* end tmporarily */
	mvaddch(player.y, player.x, CHAR);

	dangeon_genereted(max_y, max_x, &enemies, player);
	while(1) {	
		summon_enemy(enemies);
		switch(getch()) {
			case 'q':
				endwin();
				return 0;
				break;
			case 'h':
				mvplayer(0, -1, max_y, max_x, &player);
				break;
			case 'j':
				mvplayer(1, 0, max_y, max_x, &player);
				break;
			case 'k':
				mvplayer(-1, 0, max_y, max_x, &player);
				break;
			case 'l':
				mvplayer(0, 1, max_y, max_x, &player);
				break;
		}
		if(start_figth(&player, enemies)) {
			endwin();
			return 0;
		}
		clear();
		mvaddch(player.y, player.x, CHAR);
		refresh();
	}

	endwin();
	return 0;
}
