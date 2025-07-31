#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "../include/main.h"
#include "../include/dungeon.h"
#include "../include/screen.h"
#include "../include/fight.h"
#include "../include/control.h"

/* dead zone camera */
int dz_camera(gamer *player)
{
	int step = DZ_SPACE/2, res = 0;
	if(player->scr_y > (player->dz_y + step)) res = 1;
	else if(player->scr_y < (player->dz_y - step)) res = 1;
	else if(player->scr_x > (player->dz_x + step)) res = 1;
	else if(player->scr_x < (player->dz_x - step)) res = 1;
	if(res) {
		player->dz_y = player->scr_y;
		player->dz_x = player->scr_x;
		return 1;
	}
	return 0;
}
int game(int max_y, int max_x, int game_place[SIZE][SIZE], gamer *player) {
	for(;;) {
		if(move_gamer(max_y, max_x, game_place, player))
			return 0;
		if(start_fight(max_y, max_x, player, game_place))
			if(lose_screen(player, game_place))
				return 0;
		if(dz_camera(player))
			scr_replay(game_place, player, max_y, max_x);
		refresh();
	}
}

int main(int argc, char *argv[])
{
	int max_y, max_x, work_bw = 0, res, i;
	int (*game_place)[SIZE] = malloc(SIZE * sizeof(*game_place));
	gamer player;
	if(game_place == NULL) {
		perror("Error memory");
		return 1;
	}
	srand(time(NULL));
	for(i = 1; i <= argc - 1; i++) {
		if(/*argc >= 2 &&*/ strcmp(argv[i], "-bw") == 0)
			work_bw = 1;
		else
			work_bw = has_colors();
	}
	if(init_screen(&max_y, &max_x, work_bw)) {
		free(game_place);
		return 1;
	}
	preparing_the_dungeon(max_y, max_x, game_place, &player);

	res = game(max_y, max_x, game_place, &player);	

	endwin();
	return res;
}
