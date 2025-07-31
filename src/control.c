#include <ncurses.h>

#include "../include/control.h"
#include "../include/dungeon.h"
#include "../include/screen.h"

int move_gamer(int max_y, int max_x, int game_place[SIZE][SIZE],
		gamer *player)
{
	switch(getch()) {
		case QUIT_K:
			return 1;
			break;
		case REST_K:
			player->hp = MAX_HP;
			preparing_the_dungeon(max_y, max_x, game_place, player);
			break;
		case LEFT_K:
			mvplayer(0, -1, game_place, player);
			break;
		case DOWN_K:
			mvplayer(1, 0, game_place, player);
			break;
		case UP_K:
			mvplayer(-1, 0, game_place, player);
			break;
		case RIGHT_K:
			mvplayer(0, 1, game_place, player);
			break;
	}
	return 0;
}
