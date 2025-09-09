#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fight_screen.h"

int change_of_state(const int modifier, int *current, int *maximum)
{
    if(modifier == 0)
        return 0;

    if(modifier > 0) {
        if(*current >= *maximum)
        *current = (*current + modifier > *maximum) ? *maximum : *current + modifier;
    } else {
        *current = (*current + modifier <= 0) ? 0 : *current + modifier;
    }
    
    return 1;
}
static void create_bar_visual(char *buffer, int bar_width, int filled_width)
{
    int i;
    
    buffer[0] = '[';
    
    for (i = 1; i <= filled_width; i++) {
        buffer[i] = '=';
    }
    
    for (i = filled_width + 1; i < bar_width; i++) {
        buffer[i] = ' ';
    }
    
    buffer[bar_width] = ']';
    buffer[bar_width + 1] = '\0';
}
static void create_bar_info_text(char *text_buffer, int buffer_size,
		int current, int maximum, enum type_win type)
{
    if (type == sp_player) {
        snprintf(text_buffer, buffer_size, "] SP: %d/%d [", 
                current, maximum);
    } else {
        snprintf(text_buffer, buffer_size, "] HP: %d/%d [", 
                current, maximum);
    }
}
static void insert_text_into_bar(char *bar_buffer, int bar_width,
                                const char *info_text)
{
    int text_length = strlen(info_text);
    int center_pos = (bar_width - text_length) / 2;
    int i;

    for (i = 0; i < text_length && center_pos + i < bar_width; i++) {
        bar_buffer[center_pos + i + 1] = info_text[i];
    }
}
static char *create_status_bar_string(char *buffer, int buffer_size,
		int current, int maximum, enum type_win type)
{
    char info_text[32];
    int bar_width = buffer_size - 2;
    int filled_width;

    filled_width = (current * bar_width) / maximum;
    filled_width = (filled_width > bar_width) ? bar_width : filled_width;
    filled_width = (filled_width < 0) ? 0 : filled_width;

    create_bar_visual(buffer, bar_width, filled_width);
    create_bar_info_text(info_text, sizeof(info_text), current, maximum, type);
    insert_text_into_bar(buffer, bar_width, info_text);

    return buffer;
}
static void display_character_status(int y_position, enum type_win type, 
		int current_val, int max_val, int width, int color, win_t **window)
{
    char *status_bar = malloc(width + 1);
	if(status_bar == NULL)
		return;

    create_status_bar_string(status_bar, width + 1,
			current_val, max_val, type);
    
    stat_display(y_position, 1, strlen(status_bar), 
                status_bar, color, type, window);

	free(status_bar);
}
void event(int max_y, int max_x, enum type_win w, win_t **window, player_t *player,
		enemy_t *enemy)
{
	switch(w) {
		case start: break;
		case sp_player:
			display_character_status(max_y - 2 , w, player->sp,
					player->max_sp, max_x, 5, window);
			break;
		case hp_player:
			display_character_status(max_y - 1 , w, player->hp,
					player->max_hp, max_x, 4, window);
			break;
		case hp_enemy:
			display_character_status(1 , w, enemy->hp,
					enemy->max_hp, max_x, 2, window);
			break;
		case end: break;
	}
}
