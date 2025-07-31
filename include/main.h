#ifndef SUP_FUNC_H
#define SUP_FUNC_H

#define CHAR '@'
#define SIZE 1000
#define WALL '#'
#define SPACE ' '
#define FORESTER '^'
#define ENEMIES {'T', 'G', 'O', 'H'}
#define DZ_SPACE 5
#define MAX_HP 5

struct gamer {
	int y, x;
	int scr_y, scr_x;
	int dz_y, dz_x;
	int hp;
};
typedef struct gamer gamer;

#endif
