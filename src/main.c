#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "main.h"
#include "player_t.h"
#include "dungeon.h"
#include "screen.h"
#include "fight.h"
#include "fight_event.h"
#include "control.h"

#define DZ_SPACE 5

/* dead zone camera */
static int dz_camera(player_t *player)
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
static int interaction(player_t *player, int game_place[MAP_SIZE][MAP_SIZE])
{
	int i, j, c;
	for(i = -1; i <= 1; i++) {
		for(j = -1; j <= 1; j++) {
			if(is_out_of_bounds(player->y + i, player->x + j))
				continue;
			c = game_place[player->y + i][player->x + j];
			switch(c) {
				case FORESTER:
					if(winner_screen(player, game_place))
						return 1;
					break;
				case 'H':
					if(healing(1, &(player->hp), &(player->max_hp)))
						game_place[player->y + i][player->x +j] = SPACE;
					break;
			}
		}
	}
	return 0;
}
static int game(int max_y, int max_x, player_t *player, int game_place[MAP_SIZE][MAP_SIZE])
{
	for(;;) {
		if(start_fight(max_y, max_x, player, game_place))
			if(lose_screen(player, game_place))
				return 0;
		if(dz_camera(player))
			scr_replay(max_y, max_x, player, game_place);
		switch(control(player, game_place)) {
			case 0: break;
			case 1: return 0; break;
			case 2:
				if(interaction(player, game_place))
					return 0;
				break;
			case 3:
				new_game(max_y, max_x, player, game_place);
				break;
		}
		refresh();
	}
}

int main(int argc, char *argv[])
{
	int max_y, max_x, work_bw = 0, res, i;
	int (*game_place)[MAP_SIZE] = malloc(MAP_SIZE * sizeof(*game_place));
	player_t *player = malloc(sizeof(player_t));
	if(game_place == NULL) {
		perror("Error memory");
		free(player);
		return 1;
	}
	srand(time(NULL));
	for(i = 1; i <= argc - 1; i++) {
		if(strcmp(argv[i], "-bw") == 0)
			work_bw = 1;
		else
			work_bw = has_colors();
	}
	if(init_screen(&max_y, &max_x, work_bw)) {
		free(player);
		free(game_place);
		return 1;
	}
	new_game(max_y, max_x, player, game_place);

	res = game(max_y, max_x, player, game_place);	

	endwin();
	free(game_place);
	free(player);
	return res;
}
