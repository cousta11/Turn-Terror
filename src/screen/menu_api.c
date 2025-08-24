#include <stdlib.h>
#include <stdarg.h>
#include <ncurses.h>
#include <menu.h>

struct choices {
	char *name;
	struct choices *next;
};
struct menu{
	ITEM **my_items;
	MENU *menu;
	int n_choices;
	struct choices *choices;
};

void create_choices(struct choices *choices, const char *str, ...)
{

}
void create_menu(struct menu **m)
{

}
void del_menu(struct menu **m)
{
	int i;
	unpost_menu((*m)->menu);
	free_menu((*m)->menu);
    for(i = 0; i < (*m)->n_choices; ++i)
        free_item((*m)->my_items[i]);
    free((*m)->my_items);
}
