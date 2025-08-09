#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>

#include "../include/main.h"
#include "../include/screen.h"
#include "../include/dungeon.h"

struct win {
	enum type_win type;
	WINDOW *w;
	PANEL *panel;

	struct win *next;
};
void free_display(win *window)
{
	win *tmp;
	while(window) {
		tmp = window;
		switch(window->type) {
			case start: break;
			case end: break;
			case place: break;
			case panel:
				del_panel(window->panel);
				break;
			case hp_player:
				del_panel(window->panel);
				break;
			case hp_enemy:
				del_panel(window->panel);
				break;
		}
		delwin(window->w);
		window = window->next;
		free(tmp);
	}
}
win *display(enum type_win type, win *window)
{
	win *tmp = window;
	while(tmp) {
		if(tmp->type == type)
			break;
		tmp = tmp->next;
	}
	return tmp;
}
void hp_display(int win_y, int len_y, int len_x, char *str,
		int color, enum type_win type, win **window)
{
	win *tmp = display(type, *window);
	if(tmp) 
		mvwprintw(tmp->w, 0, 0, "%s", str);
	else {
		tmp = malloc(sizeof(win));
		tmp->type = type;
		tmp->w = newwin(len_y, len_x, win_y, 0);
		wattron(tmp->w, COLOR_PAIR(color));
		mvwprintw(tmp->w, 0, 0, "%s", str);
		tmp->panel = new_panel(tmp->w);
		tmp->next = *window;
		*window = tmp;
    	update_panels();
    	doupdate();
	}
	wrefresh(tmp->w);
}

int init_screen(int *max_y, int *max_x, int work_bw) {
    initscr();
    getmaxyx(stdscr, *max_y, *max_x);
	if(*max_y < 24 || *max_x < 80) {
		endwin();
		fprintf(stderr, "Error: terminal must be >= 24x80\n");
		return 1;
	}
	if(work_bw == 0) {
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
	return 0;
}
int end_screen(gamer *player, int game_place[SIZE][SIZE], int col, char *str) {
	int max_y, max_x;
	char buf[] = "quit[q] restart[r/any]\n";
	getmaxyx(stdscr, max_y, max_x);
	clear();
	attrset(COLOR_PAIR(col));
	mvaddstr(max_y/2, max_x/2 - sizeof(str)/2, str);
	mvaddstr(max_y/2 + 1, max_x/2 - sizeof(buf)/2, buf);
	if(getch() == 'q')
		return 1;
	preparing_the_dungeon(max_y, max_x, player, game_place);
	return 0;
}
int lose_screen(gamer *player, int game_place[SIZE][SIZE])
{
	if(end_screen(player, game_place, 2, "You lose!\n"))
		return 1;
	return 0;
}
int winner_screen(gamer *player, int game_place[SIZE][SIZE])
{
	if(end_screen(player, game_place, 4, "You winner!\n"))
		return 1;
	return 0;
}
void mvplayer(int mod_y, int mod_x, gamer *player, int game_place[SIZE][SIZE])
{
	int y = player->y + mod_y;
	int x = player->x + mod_x;
    if(out_the_barrier(y, x) || game_place[y][x] == WALL)
        return;
	attrset(COLOR_PAIR(1));
	mvaddch(player->scr_y, player->scr_x, game_place[player->y][player->x]);
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
				case 'O': atmvaddch(i, j, 'O', 2); break;
				case 'G': atmvaddch(i, j, 'G', 2); break;
				case 'H': atmvaddch(i, j, 'H', 4); break;
			}
		}
	}
}
void scr_replay(int max_y, int max_x, gamer *player, int game_place[SIZE][SIZE])
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
