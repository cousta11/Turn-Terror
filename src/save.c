#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "save.h"

int save_write(char file[], gamer *player, int game_plase[SIZE][SIZE])
{
	int fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if(fd == -1)
		exit(1);
	if(write(fd, player, sizeof(gamer)) == -1)
		exit(1);
	if(write(fd, game_plase, sizeof(int [SIZE][SIZE])) == -1)
		exit(1);
	close(fd);
	return 0;
}
int save_read(char file[], gamer *player, int game_plase[SIZE][SIZE])
{
	int fd;
	fd = open(file, O_RDONLY);
	if(fd == -1)
		exit(1);
	if(read(fd, player, sizeof(gamer)) == -1)
		exit(1);
	if(read(fd, game_plase, sizeof(int [SIZE][SIZE])) == -1)
		exit(1);
	close(fd);
	return 0;
}
