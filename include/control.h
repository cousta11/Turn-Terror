#ifndef CONTROL_H
#define CONTROL_H

#define QUIT_K 'q'
#define LEFT_K 'h'
#define RIGHT_K 'l'
#define UP_K 'k'
#define DOWN_K 'j'
#define REST_K 'r'
#define INTERACTION_K 'i'

#include "main.h"

int control(player_t *player, int game_place[MAP_SIZE][MAP_SIZE]);

#endif
