#include "../include/dangeon.h"

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
	int i;
	game_place[y][x] = SPACE;
	for(i = 0; i < steps; i++) {
		in_the_direction(&y, &x);
		game_place[y][x] = SPACE;
	}
}
void dangeon_genereted(int *start_y, int *start_x, int game_place[SIZE][SIZE])
{
	int y, x;
	y = *start_y = rand_to(1, SIZE);
	x = *start_x = rand_to(1, SIZE);
	drunkard(y, x, 50 * SIZE, game_place);

}
