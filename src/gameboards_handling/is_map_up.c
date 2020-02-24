/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Checks if a map stills contains unhit battleships.
*/

#include "navy_def.h"

boolean_t is_map_still_up(const char map[65])
{
    register int index = 0;

    while (index < 64) {
        if (map[index] >= '2' && map[index] <= '5')
            return (TRUE);
        index += 1;
    }
    return (FALSE);
}   