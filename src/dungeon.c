#include "../include/dungeon.h"
#include "../include/screen.h"
#include "../include/rand_to.h"


int out_the_barrier(int y, int x)
{
	return y >= SIZE || y < 0 || x >= SIZE || x < 0;
}
/* in the direction and going beyond the boundaries */
void direction(int *y, int *x)
{
	switch(rand_to(1, 4)) {
		case 1:
			if(!out_the_barrier(*y, *x - 1))
				*x -= 1;
			break;
		case 2:
			if(!out_the_barrier(*y, *x + 1))
				*x += 1;
			break;
		case 3:
			if(!out_the_barrier(*y - 1, *x))
				*y -= 1;
			break;
		case 4:
			if(!out_the_barrier(*y + 1, *x))
				*y += 1;
			break;
	}
}
/* algoritm Drunkard’s Walk */
void drunkard(int y, int x, int steps, int game_place[SIZE][SIZE])
{
	int i, ENEMIES;
	game_place[y][x] = SPACE;
	for(i = 0; i < steps; i++) {
		direction(&y, &x);
		if(game_place[y][x] == WALL) {
			if(rand_to(1, 100) < 2)
				game_place[y][x] = enemies[rand_to(0, SIZE_ENEMIES - 1)];
			else
				game_place[y][x] = SPACE;
		}
	}
	game_place[y][x] = FORESTER;
}
void dungeon_generated(int *start_y, int *start_x, int game_place[SIZE][SIZE])
{
	int y, x, i, j;
	y = *start_y = rand_to(1 + 2, SIZE - 2);
	x = *start_x = rand_to(1 + 2, SIZE - 2);
	drunkard(y, x, 50 * SIZE, game_place);
	for(i = -2; i < 3; i++)
		for(j = -2; j < 3; j++)
			game_place[y + i][x + j] = SPACE;
}
void preparing_the_dungeon(int max_y, int max_x, int game_place[SIZE][SIZE],
		gamer *player)
{
	int i, j;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			game_place[i][j] = WALL;
	dungeon_generated(&player->y, &player->x, game_place);
	scr_replay(game_place, player, max_y, max_x);
	player->dz_y = player->scr_y;
	player->dz_x = player->scr_x;
	player->hp = MAX_HP;
}
