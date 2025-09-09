#ifndef WIN_T_H
#define WIN_T_H

#include <ncurses.h>
#include "fight_screen.h"

struct win {
	enum type_win type;
	WINDOW *w;
	void *interface;
	struct win *next;
};

/*typedef struct win win_t;

int size_win_t();

enum type_win win_type(win_t *window);
void *win_window(win_t *window);
void *win_interface(win_t *window);
win_t *win_next(win_t *window);

void win_set_type(win_t *window, enum type_win type);
void win_set_window(win_t *window, void *w);
void win_set_interface(win_t *window, void *interface);
void win_set_next(win_t *window, win_t *new_window);*/


#endif
