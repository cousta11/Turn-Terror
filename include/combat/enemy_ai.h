#ifndef ENEMY_AI_H
#define ENEMY_AI_H

#include "player.h"
#include "core.h"

// Основная функция движения врагов
void move_enemies(player_t *player, int game_place[MAP_SIZE][MAP_SIZE]);

#endif
