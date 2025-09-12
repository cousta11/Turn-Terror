#include <unistd.h>

#include "core.h"
#include "player.h"

int record_a_save(int file, player_t *player, int game_place[MAP_SIZE][MAP_SIZE])
{
	if(lseek(file , 0, SEEK_SET) == (off_t)-1)
		return -1;
	if(write(file, player, sizeof(player_t)) == -1)
		return -1;
	if(write(file, game_place, sizeof(int [MAP_SIZE][MAP_SIZE])) == -1)
		return -1;
	return 0;
}
int read_the_save(int file, player_t *player, int game_place[MAP_SIZE][MAP_SIZE])
{
	if(lseek(file , 0, SEEK_SET) == (off_t)-1)
		return -1;
	if(read(file, player, sizeof(player_t)) == -1)
		return -1;
	if(read(file, game_place, sizeof(int [MAP_SIZE][MAP_SIZE])) == -1)
		return -1;
	return 0;
}
