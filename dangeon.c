#include "dangeon.h"

static char definition_of_icon(enum enemy icon)
{
	switch(icon) {
		case goblin: return 'G';
		case skeleton: return 'S';
		case troll: return 'T';
		case end: return ' ';
		case zero: return ' ';
		case start: return ' ';
	}
	return ' ';
}
static void enemy_genereted(mobs **enemies, gamer player, int min_y, int min_x,
		int max_y, int max_x)
{
	int i, y, x;
	enum enemy icon;
	for(i = 0; i < DANGEON_ENEMY; i++) {
		mobs *tmp = malloc(sizeof(mobs));
		if(!tmp) continue;
		y = rand_to(min_y, max_y);
		x = rand_to(min_x, max_x);
		if(y == player.y && x == player.x) {
			free(tmp);
			continue;
		}
		tmp->y = y;
		tmp->x = x;
		icon = rand_to(start + 1, end - 1);
		tmp->icon = definition_of_icon(icon);
		tmp->next = *enemies;
		*enemies = tmp;
	}
}
void dangeon_genereted(int max_y, int max_x, mobs **enemies, gamer player)
{
	
	enemy_genereted(&*enemies, player, 0, 0, max_y, max_x);
}
void summon_enemy(mobs *enemies)
{
	if(enemies == NULL)
		return;
	else
		summon_enemy(enemies->next);
	mvaddch(enemies->y, enemies->x, enemies->icon);
}
