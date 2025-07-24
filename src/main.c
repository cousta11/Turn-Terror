#include <string.h>
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
int finish(int x, int y, int game_place[SIZE][SIZE])
{
	int i, j;
	for(i = -1; i < 2; i++) {
		for(j = -1; j < 2; j++) {
            if(y + i < 0 || y + i >= SIZE || x + j < 0 || x + j >= SIZE)
                continue;
			if(game_place[y + i][x + j] == FORESTER)
				return 1;
		}
	}
	return 0;
}
int game(int max_y, int max_x, int game_place[SIZE][SIZE], gamer *player) {
	for(;;) {
		if(move_gamer(max_y, max_x, game_place, player))
			return 0;
		if(start_fight(max_y, max_x, player, game_place))
			if(lose_screen(max_y, max_x, player, game_place))
				return 0;
		if(dz_camera(player))
			scr_replay(game_place, player, max_y, max_x);
		if(finish(player->y, player->x, game_place))
			if(winner_screen(max_y, max_x, player, game_place))
				return 0;
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
