#include <ncurses.h>

#include "main.h"
#include "screen.h"

/* win_t */
struct win {
	enum type_win type;
	WINDOW *w;
	void *interface;
	struct win *next;
};

enum type_win win_type(win_t *window)
{
	return window == NULL ? end : window->type;
}
void *win_window(win_t *window)
{
	return window == NULL ? NULL : window->w;
}
void *win_interface(win_t *window)
{
	return window == NULL ? NULL : window->interface;
}
win_t *win_next(win_t *window)
{
	return window == NULL ? NULL : window->next;
}
int size_win_t()
{
	return sizeof(win_t);
}
void win_set_type(win_t *window, enum type_win type)
{
	window->type = type;
}
void win_set_window(win_t *window, void *w)
{
	window->w = w;
}
void win_set_interface(win_t *window, void *interface)
{
	window->interface = interface;
}
void win_set_next(win_t *window, win_t *next)
{
	window->next = next;
}
