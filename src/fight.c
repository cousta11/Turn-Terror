#include "../include/sup_func.h"
#include "../include/fight.h"

int start_fight(const int y, const int x, const int game_place[SIZE][SIZE])
{
	int ENEMIES, i, j, k;
	for(i = -2; i < 3; i++) {
		for(j = -2; j < 3; j++) {
			for(k = 0; k < SIZE_ENEMIES; k++) {
				if(game_place[y + i][x + j] == enemies[k])
					return 1;
			}
		}
	}
	return 0;
}
int fight(gamer *player, int game_place[SIZE][SIZE])
{

	return 0;
}
