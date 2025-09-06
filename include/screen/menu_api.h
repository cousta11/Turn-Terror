#ifndef MENU_API_H
#define MENU_API_H

typedef struct menu_t menu_t;

void mrefresh(menu_t *menu);
menu_t *create_menu(int y, int x, int len_y, int len_x, ... /*, NULL */);
void del_menu(menu_t **menu);

void *menu_menu(menu_t *menu);
void *menu_w(menu_t *menu);

#endif
