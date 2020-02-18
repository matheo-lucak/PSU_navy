/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** create_gameboards.c
*/

#include <stdlib.h>
#include "my.h"
#include "my_navy.h"

viewed_map_t create_gameboards(const char path_boats_pos[])
{
    viewed_map_t gameboards;

    my_memset(gameboards.ally_map, '.', 64);
    gameboards.ally_map[64] = '\0';
    my_memset(gameboards.enemy_map, '.', 64);
    gameboards.enemy_map[64] = '\0';
    return (gameboards);
}