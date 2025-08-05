#include <ncurses.h>

#include "../include/control.h"
#include "../include/dungeon.h"
#include "../include/screen.h"

int move_gamer(int max_y, int max_x, gamer *player, int game_place[SIZE][SIZE])
{
	switch(getch()) {
		case QUIT_K:
			return 1;
			break;
		case INTERACTION_K:
			return 2;
			break;
		case REST_K:
			preparing_the_dungeon(max_y, max_x, player, game_place);
			break;
		case LEFT_K:
			mvplayer(0, -1, player, game_place);
			break;
		case DOWN_K:
			mvplayer(1, 0, player, game_place);
			break;
		case UP_K:
			mvplayer(-1, 0, player, game_place);
			break;
		case RIGHT_K:
			mvplayer(0, 1, player, game_place);
			break;
	}
	return 0;
}
