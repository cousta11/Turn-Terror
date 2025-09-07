#ifndef CONTROL_H
#define CONTROL_H

#define QUIT_K 'q'
#define LEFT_K 'h'
#define RIGHT_K 'l'
#define UP_K 'k'
#define DOWN_K 'j'
#define REST_K 'r'
#define SAVE_K 's'
#define LOAD_SAVE_K 'd'
#define INTERACTION_K 'i'

#include "../include/main.h"
int move_gamer(int max_y, int max_x, char *file, gamer *player,
		int game_place[SIZE][SIZE]);

#endif
