#include <menu.h>
#include <stdlib.h>
#include <stdarg.h>

#include "menu_api.h"

void mrefresh(const menu_t *menu)
{
	post_menu(menu->menu);
	wrefresh(menu->w);
}
static void add_choice(choices_t **choice, char *str)
{
	choices_t *tmp = malloc(sizeof(choices_t)), *last = *choice;

	if(tmp == NULL)
		return;

	tmp->name = str;
	tmp->next = NULL;

	if(last == NULL) {
		*choice = tmp;
	} else {
		while(last->next != NULL)
			last = last->next;
		last->next = tmp;
	}
}
/* end arg NULL */
static void create_choice(menu_t *menu, va_list args)
{
	char *str;

	menu->n_choices = 0;
	menu->choice = NULL;

	for(;;) {
		str = va_arg(args, char *);

		if(str == NULL)
			break;

		menu->n_choices++;

		add_choice(&(menu->choice), str);
	}
}
static void del_choices(choices_t *choice)
{
	if(!choice) return;

	del_choices((choice)->next);

	free(choice);
}
static choices_t *which_choice(choices_t *choice, const int which)
{
	int i;

	for(i = 0; i < which; i++)
		choice = choice->next;

	return choice;
}
static void create_item(menu_t *menu)
{
	int i;

	menu->item = (ITEM **)calloc(menu->n_choices + 1, sizeof(ITEM *));

	if(menu->item == NULL)
		return;

	for(i = 0; i < menu->n_choices; i++)
		menu->item[i] = new_item(which_choice(menu->choice, i)->name , "");
}
menu_t *create_menu(const int y, const int x, const int len_y,
		const int len_x, ...)
{
	menu_t *menu = malloc(sizeof(menu_t));
	va_list args;

	menu->y = y;
	menu->x = x;
	menu->len_y = len_y;
	menu->len_x = len_x;

	va_start(args, len_x);
	create_choice(menu, args);
	va_end(args);

	create_item(menu);
	menu->menu = new_menu(menu->item);
	menu->w = newwin(len_y, len_x, y, x);
	set_menu_win(menu->menu, menu->w);
	set_menu_sub(menu->menu, derwin(menu->w, len_y - 2, len_x - 2, 1, 1));
	set_menu_mark(menu->menu, "> ");
	box(menu->w, 0, 0);
	return menu;
}
void del_menu(menu_t **menu)
{
	int i;

	unpost_menu((*menu)->menu);
	werase((*menu)->w);
	wrefresh((*menu)->w);

	free_menu((*menu)->menu);

	del_choices((*menu)->choice);
	for(i = 0; i < (*menu)->n_choices; i++)
		free_item((*menu)->item[i]);

	free((*menu)->item);

	delwin((*menu)->w);

	free(*menu);
	*menu = NULL;
}
