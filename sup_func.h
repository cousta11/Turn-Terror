#ifndef SUP_FUNC_H
#define SUP_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

struct gamer {
	int y;
	int x;
};
typedef struct gamer gamer;

int rand_to(int min, int max);

#endif
