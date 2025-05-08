#ifndef SUP_FUNC_H
#define SUP_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#define CHAR '@'
#define SIZE 1000
#define WALL '#'
#define SPACE ' '
#define FORESTER '^'
#define ENEMIES enemies[3] = {'G', 'O', 'T'}
#define SIZE_ENEMIES 3
#define MAX_HP 5

struct gamer {
	int y, x;
	int scr_y, scr_x;
	int hp;
};
typedef struct gamer gamer;

int rand_to(int min, int max);

#endif
