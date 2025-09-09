#include <ncurses.h>
#include <string.h>

#include "dungeon.h"
#include "control.h"
#include "menu_api.h"

#define MIN_TERMINAL_HEIGHT 24
#define MIN_TERMINAL_WIDTH 80

static void start_colors(const int work_bw)
{
	if(work_bw) return;

	start_color();

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);

	attrset(COLOR_PAIR(1));
}
int init_screen(int *max_y, int *max_x, const int work_bw)
{
	initscr();
	getmaxyx(stdscr, *max_y, *max_x);

	if(*max_y < 24 || *max_x < 80) {
		endwin();
		fprintf(stderr, "Error: terminal must be >= %dx%d\n",
				MIN_TERMINAL_HEIGHT, MIN_TERMINAL_WIDTH);
		return 1;
	}

	start_colors(work_bw);

	cbreak();
	noecho();
	curs_set(0);

	return 0;
}
static int select_act(menu_t *menu)
{
	int c;

	for(;;) {
		mrefresh(menu);

		switch(c = getch()) {
			case DOWN_K:
				menu_driver(menu->menu, REQ_DOWN_ITEM);
				break;
			case UP_K:
				menu_driver(menu->menu, REQ_UP_ITEM);
				break;
			case INTERACTION_K:
				if(item_index(current_item(menu->menu)))
					return 1;
				return 0;
				break;
		}
	}
}
static int end_screen(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE], const int col, char *str)
{
	menu_t *menu = create_menu(max_y/2 - 4/2, max_x/2 - 14/2, 4, 14,
			"continue", "exit game", NULL);

	clear();
	attrset(COLOR_PAIR(col));
	mvaddstr(max_y/2 - 4/2 - 1 , max_x/2 - strlen(str)/2, str);
	refresh();

	if(select_act(menu))
		return 1;

	new_game(max_y, max_x, player, game_place);
	del_menu(&menu);
	return 0;
}
int lose_screen(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	if(end_screen(max_y, max_x, player, game_place, 2, "You lose!\n"))
		return 1;
	return 0;
}
int winner_screen(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	if(end_screen(max_y, max_x, player, game_place, 4, "You winner!\n"))
		return 1;
	return 0;
}
void move_player(const int mod_y, const int mod_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	int y = player->y + mod_y;
	int x = player->x + mod_x;

	if(is_out_of_bounds(y, x) || game_place[y][x] == WALL)
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
void map_replay(const int y, const int x, const int max_y, const int max_x,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	int i, j, ch, cl_pair;

	for(i = 0; i < max_y; i++) {
		for(j = 0; j < max_x; j++) {
			switch(game_place[y + i][x + j]) {
				case SPACE: ch = SPACE; cl_pair = 1; break;
				case WALL: ch = WALL; cl_pair = 1; break;
				case OUT: ch = OUT; cl_pair = 3; break;
				case 'T': ch = 'T'; cl_pair = 2; break;
				case 'O': ch = 'O'; cl_pair = 2; break;
				case 'G': ch = 'G'; cl_pair = 2; break;
				case 'H': ch = 'H'; cl_pair = 4; break;
			}

			attrset(COLOR_PAIR(cl_pair));
			mvaddch(i, j, ch);
		}
	}
}
void scr_replay(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	int y = player->y - (max_y/2);
	int x = player->x - (max_x/2);

	if(y < 0) y = 0;
	if(x < 0) x = 0;
	if(y + max_y >= MAP_SIZE) y = MAP_SIZE - max_y;
	if(x + max_x >= MAP_SIZE) x = MAP_SIZE - max_x;

	clear();
	map_replay(y, x, max_y, max_x, game_place);
	attrset(COLOR_PAIR(1));

	player->scr_y = player->y - y;
	player->scr_x = player->x - x;
	if(player->scr_y >= 0 && player->scr_y < max_y &&
	    player->scr_x >= 0 && player->scr_x < max_x) {
	    mvaddch(player->scr_y, player->scr_x, CHAR);
	}
}
