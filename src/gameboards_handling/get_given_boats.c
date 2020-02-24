/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** get_given_boats.c
*/

#include <fcntl.h>
#include "my.h"
#include "navy.h"

static boolean_t treat_battleship(const int fd, ship_t *ship,
                                    const int battleship_nb)
{
    static char boats_lengths[4] = {0, 0, 0, 0};
    char **splitted_line = NULL;

    splitted_line = my_str_to_word_array(get_next_line(fd), ":", 1);
    if (!treat_boat_line(ship, splitted_line)) {
        my_free_arr((void **)splitted_line);
        close(fd);
        return (FALSE);
    }
    boats_lengths[battleship_nb] = splitted_line[0][0];
    my_free_arr((void **)splitted_line);
    if (!check_boats_lengths(boats_lengths, battleship_nb)) {
        close(fd);
        return (FALSE);
    }
    close(fd);
    return (TRUE);
}

static boolean_t place_battleship(const ship_t ship, char ally_map[65])
{
    int boat_index = get_target_aim(ship.begin[0], ship.begin[1]);
    int offset = ship.begin[0] - ship.end[0] == 0 ? 8 : 1;
    int index = 0;

    while (index < ship.len) {
        if (ally_map[boat_index] != '.')
            return (FALSE);
        ally_map[boat_index] = ship.len + '0';
        boat_index += offset;
        index += 1;
    }
    return (TRUE);
}

boolean_t get_given_boats(char ally_map[65], const char path_boats_pos[])
{
    const int fd = open(path_boats_pos, O_RDONLY);
    ship_t ship = {0, {0, 0}, {0, 0}};
    int index = 0;

    if (fd == -1)
        return (FALSE);
    while (index < 4) {
        if (!treat_battleship(fd, &ship, index))
            return (FALSE);
        if (!place_battleship(ship, ally_map))
            return (FALSE);
        index += 1;
    }
    if (leftovers_in_file(fd))
        return (FALSE);
    return (TRUE);
}