#ifndef SCREEN_H
#define SCREEN_H

#include "sup_func.h"
void mvplayer(int mod_y, int mod_x, int arr[SIZE][SIZE], struct gamer *player);
void atmvaddch(int y, int x, int c, int cl_pair);
void map_replay(int y, int x, int max_y, int max_x, int game_place[SIZE][SIZE]);
void scr_replay(int game_place[SIZE][SIZE], gamer *player, int max_y, int max_x);

#endif
