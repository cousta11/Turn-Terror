#ifndef SAVE_H
#define SAVE_H

#include "core.h"
#include "player.h"

int record_a_save(int file, player_t *player, int game_place[MAP_SIZE][MAP_SIZE]);
int read_the_save(int file, player_t *player, int game_place[MAP_SIZE][MAP_SIZE]);

#endif
