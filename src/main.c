#include <string.h>
#include "../include/main.h"
#include "../include/dungeon.h"
#include "../include/screen.h"
#include "../include/fight.h"
#include "../include/control.h"

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
int game(int max_y, int max_x, int game_place[SIZE][SIZE], gamer *player) {
	int combat, enemy_y, enemy_x, i = 0;
	for(;;) {
			if(move_gamer(max_y, max_x, game_place, player))
				return 0;

			if(start_fight(player->y, player->x, &enemy_y, &enemy_x, game_place)) {
				combat = fight(max_y, max_x, enemy_y, enemy_x, player, game_place);
				if(!combat) {
					lose_screen(max_y, max_x, player, game_place);
				} else {
	    			getmaxyx(stdscr, max_y, max_x);
					scr_replay(game_place, player, max_y, max_x);
				}
			}

			if(i == 10) {
	    		getmaxyx(stdscr, max_y, max_x);
				scr_replay(game_place, player, max_y, max_x);
				i = 0;
			} else i++;
			if(finish(player->y, player->x, game_place))
				if(winner_screen(max_y, max_x, player, game_place))
					return 0;
			refresh();
		}
}

int main(int argc, char *argv[])
{
	int max_y, max_x, work_bw = 0, res;
	int (*game_place)[SIZE] = malloc(SIZE * sizeof(*game_place));
	gamer player;
	if(game_place == NULL) {
		perror("Error memory");
		return 1;
	}
	srand(time(NULL));
	if(argc >= 2 && strcmp(argv[1], "-bw") == 0)
		work_bw = 1;
	else
		work_bw = has_colors();
	if(init_screen(&max_y, &max_x, work_bw)) {
		free(game_place);
		return 1;
	}
	player.hp = MAX_HP;
	preparing_the_dungeon(max_y, max_x, game_place, &player);

	res = game(max_y, max_x, game_place, &player);	

	endwin();
	return res;
}
