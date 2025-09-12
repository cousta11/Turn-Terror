#include <ncurses.h>

#include "player.h"
#include "core.h"
#include "control.h"
#include "ui.h"

int control(player_t *player, int game_place[MAP_SIZE][MAP_SIZE])
{
	int mod_y = 0, mod_x = 0;

	switch(getch()) {
		case QUIT_K: return 1; break;
		case INTERACTION_K: return 2; break;
		case REST_K: return 3; break;
		case SAVE_WRITE_K: return 4; break;
		case SAVE_READ_K: return 5; break;
		case LEFT_K: mod_x = -1; break;
		case DOWN_K: mod_y = 1; break;
		case UP_K: mod_y = -1; break;
		case RIGHT_K: mod_x = 1; break;
	}

	move_player(mod_y, mod_x, player, game_place);

	return 0;
}
