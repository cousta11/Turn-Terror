#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <stdlib.h>

#include "fight.h"
#include "fight_screen.h"
#include "fight_event.h"
#include "win_t.h"

void refresh_fight(int max_y, int max_x, win_t *window, player_t *player,
		enemy_t *enemy)
{
	enum type_win event_type;
	for(event_type = start; event_type < end; event_type++)
		event(max_y, max_x, event_type, &window, player, enemy);
}
win_t *display(enum type_win type, win_t *window)
{
	win_t *tmp = window;
	while(tmp) {
		if(tmp->type == type)
			break;
		tmp = tmp->next;
	}
	return tmp;
}
void hp_display(int win_y, int len_y, int len_x, char *str,
		int color, enum type_win type, win_t **window)
{
	win_t *tmp = display(type, *window);
	if(tmp) 
		mvwprintw(tmp->w, 0, 0, "%s", str);
	else {
		tmp = malloc(sizeof(win_t));
		tmp->type = type;
		tmp->w = newwin(len_y, len_x, win_y, 0);
		wattron(tmp->w, COLOR_PAIR(color));
		mvwprintw(tmp->w, 0, 0, "%s", str);
		tmp->interface = new_panel(tmp->w);
		tmp->next = *window;
		*window = tmp;
		update_panels();
		doupdate();
	}
	wrefresh(tmp->w);
}
void free_display(win_t *window)
{
	if(window)
		free_display(window);
	switch(window->type) {
		case start: break;
		case sp_player: del_panel(window->interface); break;
		case hp_player: del_panel(window->interface); break;
		case hp_enemy: del_panel(window->interface); break;
		case end: break;
	}
	delwin(window->w);
	free(window);
}
