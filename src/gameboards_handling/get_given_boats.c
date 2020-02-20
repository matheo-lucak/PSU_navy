/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** get_given_boats.c
*/

#include <fcntl.h>
#include "my.h"
#include "my_navy.h"

static boolean_t treat_each_ship(const int fd, ship_t *ship,
                                const size_t index)
{
    char * restrict * restrict splitted_line = NULL;
    static char boats_lengths[4];

    splitted_line = my_str_to_word_array(get_next_line(fd, 9), ":", 1);
    if (!treat_line(ship, splitted_line)) {
        my_free_arr((void **)splitted_line);
        return (FALSE);
    }
    boats_lengths[index] = splitted_line[0][0];
    my_free_arr((void **)splitted_line);
    if (!check_boats_lengths(boats_lengths, index))
        return (FALSE);
    return (TRUE);
}

static boolean_t place_each_ship(const ship_t ship, char ally_map[65])
{
    register size_t boat_index = 8 * (ship.begin[1] - 49) + ship.begin[0] - 65;
    register size_t index = 0;
    register size_t offset = 1;

    if (!(ship.begin[0] - ship.end[0]))
        offset = 8;
    while (index < ship.len) {
        if (ally_map[boat_index] != '.')
            return (FALSE);
        ally_map[boat_index] = ship.len + 48;
        boat_index += offset;
        index += 1;
    }
    return (TRUE);
}

boolean_t get_given_boats(char ally_map[65], const char path_boats_pos[])
{
    const int fd = open(path_boats_pos, O_RDONLY);
    register size_t index = 0;
    ship_t ship;

    if (fd == -1)
        return (FALSE);
    while (index < 4) {
        if (!treat_each_ship(fd, &ship, index))
            return (FALSE);
        if (!place_each_ship(ship, ally_map))
            return (FALSE);
        index += 1;
    }
    if (!check_too_many_chars(fd))
        return (FALSE);
    return (TRUE);
}