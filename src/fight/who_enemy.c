#include <stdlib.h>

#include "fight.h"


struct enemy *who_enemy(char c)
{
	struct enemy *enemy = malloc(sizeof(struct enemy));
	enemy->hp = 0;
	switch(c) {
		case 'T':
			enemy->max_hp = enemy->hp = 15;
			enemy->name = "Troll";
			break;
		case 'O':
			enemy->max_hp = enemy->hp = 8;
			enemy->name = "Orc";
			break;
		case 'G':
			enemy->max_hp = enemy->hp = 5;
			enemy->name = "Goblin";
			break;
	}
	return enemy;
}
