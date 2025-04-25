#include "../include/dangeon.h"

/* algoritm Drunkard’s Walk */
void drunkard(int y, int x, int steps, int *game_place[SIZE][SIZE])
{
	int i;
	*game_place[y, x] = WALL;
	for(i = 0; i < steps; i++) {

	}
}
void dangeon_genereted(int *start_y, int *start_x, int *game_place[SIZE][SIZE])
{
	int y, x;
	y = *start_y = rand_to(1, SIZE);
	x = *start_x = rand_to(1, SIZE);
	drunkard(y, x, 50 * SIZE, game_place);

}
