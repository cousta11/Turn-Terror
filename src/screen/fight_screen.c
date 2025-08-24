#include <ncurses.h>
#include <panel.h>
#include <menu.h>
#include <stdlib.h>

#include "main.h"
#include "screen.h"

win_t *display(enum type_win type, win_t *window)
{
	win_t *tmp = window;
	while(tmp) {
		if(win_type(tmp) == type)
			break;
		tmp = win_next(tmp);
	}
	return tmp;
}
void hp_display(int win_y, int len_y, int len_x, char *str,
		int color, enum type_win type, win_t **window)
{
	win_t *tmp = display(type, *window);
	if(tmp) 
		mvwprintw(win_window(tmp), 0, 0, "%s", str);
	else {
		tmp = malloc(size_win_t());
		win_set_type(tmp, type);
		win_set_window(tmp, newwin(len_y, len_x, win_y, 0));
		wattron(win_window(tmp), COLOR_PAIR(color));
		mvwprintw(win_window(tmp), 0, 0, "%s", str);
		win_set_interface(tmp, new_panel(win_window(tmp)));
		win_set_next(tmp, *window);
		*window = tmp;
    	update_panels();
    	doupdate();
	}
	wrefresh(win_window(tmp));
}
void free_display(win_t *window)
{
	if(window)
		free_display(win_next(window));
	switch(win_type(window)) {
		case start: break;
		case place: break;
		case menu: break;
		case panel: del_panel(win_interface(window)); break;
		case hp_player: del_panel(win_interface(window)); break;
		case hp_enemy: del_panel(win_interface(window)); break;
		case end: break;
	}
	delwin(win_window(window));
	free(window);
}
