#ifndef PLAYER_H
#define PLAYER_H

typedef struct player_t{
	int y, x;
	int scr_y, scr_x;
	int dz_y, dz_x;
	int hp, max_hp;
	int sp, max_sp;
	int dmg;
	int armor;
	int mod_sp;
	char *save_file;
} player_t;

#endif
