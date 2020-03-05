/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Updates a map with a hit or a miss.
*/

#include "navy_connect.h"

boolean_t update_map(char map[65], const binary_signal_t target)
{
    if (map[target.bridge] >= '2' && map[target.bridge] <= '5') {
        map[target.bridge] = 'x';
        return (TRUE);
    } else if (map[target.bridge] == '.')
        map[target.bridge] = 'o';
    return (FALSE);
}