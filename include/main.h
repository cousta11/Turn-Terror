#ifndef SUP_FUNC_H
#define SUP_FUNC_H

#define CHAR '@'
#define SIZE 1000
#define WALL '#'
#define SPACE ' '
#define FORESTER '^'
#define ENEMIES {'T', 'G', 'O'}
#define OBJECT {'H'}
#define DZ_SPACE 5
#define START_MAX_HP 5

struct gamer {
	int y, x;
	int scr_y, scr_x;
	int dz_y, dz_x;
	int hp, max_hp;
};
typedef struct gamer gamer;
typedef struct win win;
enum type_win {start = 0, panel, place, hp_player, hp_enemy, end};

#endif
