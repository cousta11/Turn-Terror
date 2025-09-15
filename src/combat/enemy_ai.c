#include <stdlib.h>

#include "dungeon.h"

#define AGRO_RADIUS 7

static int is_walkable(const int x, const int y,
	                   const int map[MAP_SIZE][MAP_SIZE])
{
	char cell = map[y][x];
	
	if(is_out_of_bounds(y, x))
	    return 0;
	
	return (cell == SPACE);
}

static int is_enemy_char(const char c)
{
	int i;
	char enemies[] = ENEMIES;
	
	for(i = 0; i < sizeof(enemies); i++)
	    if(c == enemies[i])
	        return 1;
	
	return 0;
}

static int should_move_enemy(const int x, const int y, const player_t *player)
{
	int distance = abs(x - player->x) + abs(y - player->y);
	return (distance <= AGRO_RADIUS && distance > 1);
}

static int try_move_horizontal(int x, int y, int dx,
		int game_place[MAP_SIZE][MAP_SIZE], int new_positions[MAP_SIZE][MAP_SIZE])
{
	int new_x = x + (dx > 0 ? 1 : -1);
	
	if(is_walkable(new_x, y, game_place)) {
	    new_positions[y][x] = SPACE;
	    new_positions[y][new_x] = game_place[y][x];
	    return 1;
	}

	return 0;
}

static int try_move_vertical(int x, int y, int dy,
		int game_place[MAP_SIZE][MAP_SIZE], int new_positions[MAP_SIZE][MAP_SIZE])
{
	int new_y = y + (dy > 0 ? 1 : -1);
	
	if(is_walkable(x, new_y, game_place)) {
	    new_positions[y][x] = SPACE;
	    new_positions[new_y][x] = game_place[y][x];
	    return 1;
	}
	return 0;
}

static void move_single_enemy(int x, int y, const player_t *player,
		int game_place[MAP_SIZE][MAP_SIZE], int new_positions[MAP_SIZE][MAP_SIZE])
{
	int dx = player->x - x;
	int dy = player->y - y;
	int moved = 0;
	
	if(abs(dx) > abs(dy)) {
	    moved = try_move_horizontal(x, y, dx, game_place, new_positions);
	    if(!moved) {
	        try_move_vertical(x, y, dy, game_place, new_positions);
		}
	} else {
	    moved = try_move_vertical(x, y, dy, game_place, new_positions);
	    if(!moved) {
	        try_move_horizontal(x, y, dx, game_place, new_positions);
		}
	}
}
static void locate_enemy(const int game_place[MAP_SIZE][MAP_SIZE],
		int new_positions[MAP_SIZE][MAP_SIZE])
{
	int x, y;
	for(y = 0; y < MAP_SIZE; y++)
	    for(x = 0; x < MAP_SIZE; x++)
	        if(is_enemy_char(game_place[y][x]))
	            new_positions[y][x] = game_place[y][x];
}

void move_enemies(const player_t *player, int game_place[MAP_SIZE][MAP_SIZE])
{
	int new_positions[MAP_SIZE][MAP_SIZE] = {0};
	int y, x;
	
	locate_enemy(game_place, new_positions);
	
	for(y = 0; y < MAP_SIZE; y++) {
	    for(x = 0; x < MAP_SIZE; x++) {
	        if(!is_enemy_char(game_place[y][x])) continue;
	        if(!should_move_enemy(x, y, player)) continue;
	        move_single_enemy(x, y, player, game_place, new_positions);
	    }
	}
	
	for(y = 0; y < MAP_SIZE; y++)
	    for(x = 0; x < MAP_SIZE; x++)
	        if(new_positions[y][x] != 0)
	            game_place[y][x] = new_positions[y][x];
	        else if(is_enemy_char(game_place[y][x]))
	            game_place[y][x] = SPACE;
}
