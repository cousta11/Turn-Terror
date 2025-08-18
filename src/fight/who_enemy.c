#include <stdlib.h>

#include "fight.h"

struct enemy *create_enemy(int hp, int dmg, int armor, char *name)
{
	struct enemy *enemy = malloc(sizeof(struct enemy));
	enemy->max_hp = enemy->hp = hp;
	enemy->dmg = dmg;
	enemy->armor = armor;
	enemy->name = name;
	return enemy;
}

struct enemy *who_enemy(char c)
{
	struct enemy *enemy = NULL;
	switch(c) {
		case 'T': enemy = create_enemy(15, 3, 2, "Troll"); break;
		case 'O': enemy = create_enemy(8, 3, 2, "Orc"); break;
		case 'G': enemy = create_enemy(5, 3, 2, "Goblin"); break;
	}
	return enemy;
}
