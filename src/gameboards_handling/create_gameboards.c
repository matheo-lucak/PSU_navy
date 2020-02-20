/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** create_gameboards.c
*/

#include <stdlib.h>
#include "my.h"
#include "my_navy.h"

boolean_t create_gameboards(viewed_map_t *gameboards,
                            const char path_boats_pos[])
{
    my_memset(gameboards->ally_map, '.', 64);
    gameboards->ally_map[64] = '\0';
    if (!get_given_boats(gameboards->ally_map, path_boats_pos))
        return (FALSE);
    my_memset(gameboards->enemy_map, '.', 64);
    gameboards->enemy_map[64] = '\0';
    return (TRUE);
}