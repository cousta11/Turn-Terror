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

struct gamer {
	int y;
	int x;
	int lvl;
	int max_hp;
	int hp;
	int max_mp;
	int mp;
};
typedef struct gamer gamer;
enum enemy {zero, start, goblin, skeleton, troll, end};

int rand_to(int min, int max);

#endif
