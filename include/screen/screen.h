#ifndef SCREEN_H
#define SCREEN_H

#include "main.h"

typedef struct win win_t;

void hp_display(int win_y, int len_y, int len_x, char *str,
		int color, enum type_win type, win_t **window);
void free_display(win_t *window);
int init_screen(int *max_y, int *max_x, int work_bw);
void mvplayer(int mod_y, int mod_x, gamer *player, int game_place[SIZE][SIZE]);
void atmvaddch(int y, int x, int c, int cl_pair);
void map_replay(int y, int x, int max_y, int max_x, int game_place[SIZE][SIZE]);
void scr_replay(int max_y, int max_x, gamer *player, int game_place[SIZE][SIZE]);
int winner_screen(gamer *player, int game_place[SIZE][SIZE]);
int lose_screen(gamer *player, int game_place[SIZE][SIZE]);
win_t *display(enum type_win type, win_t *window);

/* win_t functions */
int size_win_t();
enum type_win win_type(win_t *window);
void *win_window(win_t *window);
void *win_interface(win_t *window);
win_t *win_next(win_t *window);
void win_set_type(win_t *window, enum type_win type);
void win_set_window(win_t *window, void *w);
void win_set_interface(win_t *window, void *interface);
void win_set_next(win_t *window, win_t *new_window);

#endif
