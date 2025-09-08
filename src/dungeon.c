#include "main.h"
#include "dungeon.h"
#include "screen.h"
#include "random_range.h"

#define START_MAX_HP 5
#define START_MAX_SP 5
#define START_MOD_SP 5
#define BASE_DMG 3
#define BASE_ARMOR 2
#define RANGE_DURNCARD 50 * MAP_SIZE

static void direction(int *y, int *x)
{
	int new_y = *y, new_x = *x;

	switch(random_range(1, 4)) {
		case 1: new_x--; break;
		case 2: new_x++; break;
		case 3: new_y--; break;
		case 4: new_y++; break;
	}

	if(!(is_out_of_bounds(new_y, new_x))) {
		*y = new_y;
		*x = new_x;
	}
}
/* algoritm Drunkard’s Walk */
static void drunkard(int y, int x, const int steps,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	int i, enemy[] = ENEMIES, obj[] = OBJECT, random_number;

	game_place[y][x] = SPACE;

	for(i = 0; i < steps; i++) {
		direction(&y, &x);
		if(game_place[y][x] == WALL) {
			random_number = random_range(1, 1000);
			if(random_number < 20)
				game_place[y][x] = enemy[random_range(0, sizeof(enemy)/sizeof(int) - 1)];
			else if(random_number <= 23)
				game_place[y][x] = obj[random_range(0, sizeof(obj)/sizeof(int)- 1)];
			else
				game_place[y][x] = SPACE;
		}
	}

	game_place[y][x] = FORESTER;
}
static void dungeon_generated(int *start_y, int *start_x,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	int y, x, i, j;

	y = *start_y = random_range(1 + 2, MAP_SIZE - 2);
	x = *start_x = random_range(1 + 2, MAP_SIZE - 2);

	for(i = 0; i < MAP_SIZE; i++)
		for(j = 0; j < MAP_SIZE; j++)
			game_place[i][j] = WALL;

	drunkard(y, x, 50 * MAP_SIZE, game_place);

	for(i = -2; i < 3; i++)
		for(j = -2; j < 3; j++)
			if(game_place[y + i][x + j] != FORESTER)
				game_place[y + i][x + j] = SPACE;
}
static void new_player(gamer *player)
{
	player->dz_y = player->scr_y;
	player->dz_x = player->scr_x;
	player->hp = player->max_hp = START_MAX_HP;
	player->sp = player->max_sp = START_MAX_SP;
	player->mod_sp = START_MOD_SP;
	player->dmg = BASE_DMG;
	player->armor = BASE_ARMOR;
}

int is_out_of_bounds(const int y, const int x)
{
	return y >= MAP_SIZE || y < 0 || x >= MAP_SIZE || x < 0;
}
void new_game(const int max_y, const int max_x, gamer *player,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	dungeon_generated(&player->y, &player->x, game_place);
	scr_replay(max_y, max_x, player, game_place);
	new_player(player);
}
