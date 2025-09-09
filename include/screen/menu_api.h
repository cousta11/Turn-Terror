#ifndef MENU_API_H
#define MENU_API_H

#include <ncurses.h>
#include <menu.h>

typedef struct choices_t {
	char *name;
	struct choices_t *next;
} choices_t;

typedef struct menu_t {
	ITEM **item;
	WINDOW *w;
	MENU *menu;
	choices_t *choice;
	int n_choices;
	int y, x, len_y, len_x;
} menu_t;

void mrefresh(menu_t *menu);
menu_t *create_menu(int y, int x, int len_y, int len_x, ... /*, NULL */);
void del_menu(menu_t **menu);

#endif
