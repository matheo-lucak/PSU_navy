/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Updates a map with a hit or a miss.
*/

#include "navy_connect.h"

boolean_t update_map(char map[65], const char pos)
{
    if (map[pos] >= '2' && map[pos] <= '5') {
        map[pos] = 'x';
        return (TRUE);
    } else if (map[pos] == '.')
        map[pos] = 'o';
    return (FALSE);
}