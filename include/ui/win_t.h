#ifndef WIN_T_H
#define WIN_T_H

#include <ncurses.h>
#include "combat_ui.h"

typedef struct win {
	enum type_win type;
	WINDOW *w;
	void *interface;
	struct win *next;
} win_t;

#endif
