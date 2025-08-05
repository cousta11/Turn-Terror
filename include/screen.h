#ifndef SCREEN_H
#define SCREEN_H

#include "main.h"

void hp_display(int win_y, int win_x, int len_y, int len_x, char *str,
		int color, win **window);
void free_display(win *window);
int init_screen(int *max_y, int *max_x, int work_bw);
void mvplayer(int mod_y, int mod_x, gamer *player, int game_place[SIZE][SIZE]);
void atmvaddch(int y, int x, int c, int cl_pair);
void map_replay(int y, int x, int max_y, int max_x, int game_place[SIZE][SIZE]);
void scr_replay(int max_y, int max_x, gamer *player, int game_place[SIZE][SIZE]);
int winner_screen(gamer *player, int game_place[SIZE][SIZE]);
int lose_screen(gamer *player, int game_place[SIZE][SIZE]);

#endif
