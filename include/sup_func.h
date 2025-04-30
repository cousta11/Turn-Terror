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

struct gamer {
	int y, x;
	int scr_y, scr_x;
	int lvl;
	int max_hp, hp;
	int max_mp, mp;
};
typedef struct gamer gamer;

int rand_to(int min, int max);

#endif
