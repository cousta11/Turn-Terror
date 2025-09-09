#include <stdlib.h>

#include "combat.h"
#include "enemy.h"

static enemy_t *create_enemy(const int hp, const int dmg, const int armor,
		char *name)
{
	enemy_t *enemy = malloc(sizeof(enemy_t));
	enemy->max_hp = enemy->hp = hp;
	enemy->dmg = dmg;
	enemy->armor = armor;
	enemy->name = name;
	return enemy;
}

enemy_t *who_enemy(const char ch)
{
	enemy_t *enemy = NULL;
	switch(ch) {
		case 'T': enemy = create_enemy(15, 2, 2, "Troll"); break;
		case 'O': enemy = create_enemy(8, 1, 1, "Orc"); break;
		case 'G': enemy = create_enemy(5, 1, 0, "Goblin"); break;
	}
	return enemy;
}
