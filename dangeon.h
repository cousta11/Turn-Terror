#ifndef DANGEON_H
#define DANGEON_H

#include "sup_func.h"
#define DANGEON_ROW 100
#define DANGEON_COL 100
#define DANGEON_ENEMY 5
void dangeon_genereted(int max_y, int max_x, mobs **enemies, gamer player);
void summon_enemy(mobs *enemies);

#endif
