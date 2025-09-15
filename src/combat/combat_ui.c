#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <stdlib.h>

#include "combat_ui.h"
#include "combat_event.h"
#include "win_t.h"

void refresh_fight(const int max_y, const int max_x, win_t **window,
		player_t *player, enemy_t *enemy)
{
	enum type_win event_type;
	for(event_type = start; event_type < end; event_type++)
		event(max_y, max_x, event_type, window, player, enemy);
}
win_t *display(const enum type_win type, win_t *window)
{
	win_t *tmp = window;

	while(tmp) {
		if(tmp->type == type)
			break;
		tmp = tmp->next;
	}

	return tmp;
}
void state_display(const int win_y, const int len_y, const int len_x, const char *str,
		const int color, const enum type_win type, win_t **window)
{
	win_t *tmp = display(type, *window);

	if(tmp)
		mvwprintw(tmp->w, 0, 0, "%s", str);
	else {
		tmp = malloc(sizeof(win_t));
		if(tmp == NULL) return;
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
void free_display(win_t *window_list)
{
	win_t *tmp;
	while(window_list != NULL) {
		tmp = window_list->next;
		switch(window_list->type) {
		    case start:
		    case end:
		        break;
		    case sp_player:
		    case hp_player: 
		    case hp_enemy:
		        del_panel(window_list->interface);
				delwin(window_list->w);
		        break;
		}
		free(window_list);
		window_list = tmp;
	}
}
