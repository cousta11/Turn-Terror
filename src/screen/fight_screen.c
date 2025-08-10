#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>

#include "main.h"
#include "screen.h"

void free_display(win *window)
{
	win *tmp;
	while(window) {
		tmp = window;
		switch(window->type) {
			case start: break;
			case end: break;
			case place: break;
			case panel:
				del_panel(window->panel);
				break;
			case hp_player:
				del_panel(window->panel);
				break;
			case hp_enemy:
				del_panel(window->panel);
				break;
		}
		delwin(window->w);
		window = window->next;
		free(tmp);
	}
}
win *display(enum type_win type, win *window)
{
	win *tmp = window;
	while(tmp) {
		if(tmp->type == type)
			break;
		tmp = tmp->next;
	}
	return tmp;
}
void hp_display(int win_y, int len_y, int len_x, char *str,
		int color, enum type_win type, win **window)
{
	win *tmp = display(type, *window);
	if(tmp) 
		mvwprintw(tmp->w, 0, 0, "%s", str);
	else {
		tmp = malloc(sizeof(win));
		tmp->type = type;
		tmp->w = newwin(len_y, len_x, win_y, 0);
		wattron(tmp->w, COLOR_PAIR(color));
		mvwprintw(tmp->w, 0, 0, "%s", str);
		tmp->panel = new_panel(tmp->w);
		tmp->next = *window;
		*window = tmp;
    	update_panels();
    	doupdate();
	}
	wrefresh(tmp->w);
}
