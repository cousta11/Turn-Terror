#include "fight.h"

int fight(gamer *player, mobs *enemy)
{
	clear();
	move(0, 0);
	addstr("You win!");
	switch(getch()) {
		case ' ': return 0;
	}
	return 0;
}
int start_figth(gamer *player, mobs *enemies)
{
	mobs *prev = NULL, *tmp = enemies;
	if(tmp == NULL)
		return 0;
	while(tmp) {
		if(tmp->y == player->y && tmp->x == player->x) {
			if(fight(player, tmp)) {
				return 1;
			} else {
				if(!prev) {
					free(enemies);
					enemies = NULL;
					return 0;
				} else {
					prev->next = tmp->next;
					free(tmp);
				}

			}
		}
		prev = tmp;
		tmp = prev->next;
	}
	return 0;
}
