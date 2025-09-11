#include "core.h"
#include "dungeon.h"
#include "ui.h"
#include "random.h"

#define START_MAX_HP 5
#define START_MAX_SP 10
#define START_MOD_SP 0
#define BASE_DMG 3
#define BASE_ARMOR 2
#define RANGE_DRUNKARD 50 * MAP_SIZE
#define CHANCE_SPAWN_ENEMY 20    /* 2% chance spawn enemy (from 1000) */
#define CHANCE_SPAWN_OBJECT 3    /* 0.3% chance spawn object (from 1000) */

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
			if(random_number < CHANCE_SPAWN_ENEMY)
				game_place[y][x] = enemy[random_range(0, sizeof(enemy)/sizeof(int) - 1)];
			else if(random_number < CHANCE_SPAWN_ENEMY + CHANCE_SPAWN_OBJECT)
				game_place[y][x] = obj[random_range(0, sizeof(obj)/sizeof(int)- 1)];
			else
				game_place[y][x] = SPACE;
		}
	}

	game_place[y][x] = OUT;
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

	drunkard(y, x, RANGE_DRUNKARD, game_place);

	for(i = -2; i < 3; i++)
		for(j = -2; j < 3; j++)
			if(game_place[y + i][x + j] != OUT)
				game_place[y + i][x + j] = SPACE;
}
static void new_player(player_t *player)
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
void new_game(const int max_y, const int max_x, player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE])
{
	dungeon_generated(&player->y, &player->x, game_place);
	scr_replay(max_y, max_x, player, game_place);
	new_player(player);
}
