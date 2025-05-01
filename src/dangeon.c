#include "../include/dangeon.h"
#include "../include/screen.h"

int out_the_barrier(int y, int x)
{
	return y >= SIZE || y < 1 || x >= SIZE || x < 1;
}
/* in the direction and going beyond the boundaries */
void in_the_direction(int *y, int *x)
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
	int i, enemy[3] = {'G', 'O', 'T'};
	game_place[y][x] = SPACE;
	for(i = 0; i < steps; i++) {
		in_the_direction(&y, &x);
		if(game_place[y][x] == WALL) {
			if(rand_to(1, 100) < 2)
				game_place[y][x] = enemy[rand_to(0, 1)];
			else
				game_place[y][x] = SPACE;
		}
	}
	game_place[y][x] = FORESTER;
}
void dangeon_genereted(int *start_y, int *start_x, int game_place[SIZE][SIZE])
{
	int y, x;
	y = *start_y = rand_to(1, SIZE);
	x = *start_x = rand_to(1, SIZE);
	drunkard(y, x, 50 * SIZE, game_place);

}
void preparing_the_dungeon(int max_y, int max_x, int game_place[SIZE][SIZE],
		gamer *player)
{
	int i, j;
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			game_place[i][j] = WALL;
	dangeon_genereted(&player->y, &player->x, game_place);
	scr_replay(game_place, player, max_y, max_x);

}
