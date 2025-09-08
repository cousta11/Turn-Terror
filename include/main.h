#ifndef SUP_FUNC_H
#define SUP_FUNC_H

#define CHAR '@'
#define MAP_SIZE 1000
#define WALL '#'
#define SPACE ' '
#define FORESTER '^'
#define ENEMIES {'T', 'G', 'O'}
#define OBJECT {'H'}

struct gamer {
	int y, x;
	int scr_y, scr_x;
	int dz_y, dz_x;
	int hp, max_hp;
	int sp, max_sp;
	int dmg, armor;
	int mod_sp;
};
typedef struct gamer gamer;
enum type_win {start = 0, sp_player, hp_player, hp_enemy, end};

#endif
