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
#define START_MAX_SP 5
#define BASE_DMG 3
#define BASE_ARMOR 2

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
