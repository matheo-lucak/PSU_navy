/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Handles errors from a given battleships file
*/

#include <stdlib.h>
#include "my.h"
#include "navy.h"

boolean_t check_too_many_chars(const int fd)
{
    char *line = NULL;

    line = get_next_line(fd);
    if (line) {
        free(line);
        return (FALSE);
    }
    return (TRUE);
}

boolean_t check_boats_lengths(const char boats_lengths[4], const int len)
{
    register int index = 0;
    char has_been_done[4] = "0000";

    while (index <= len) {
        if (boats_lengths[index] < '2' || boats_lengths[index] > '5')
            return (FALSE);
        if (has_been_done[boats_lengths[index] - 50] == '0')
            has_been_done[boats_lengths[index] - 50] = '1';
        else
            return (FALSE);
        index += 1;
    }
    return (TRUE);
}

static boolean_t fill_edges_coords(char *line, char value[2])
{
    value[0] = line[0];
    if (value[0] < 'A' || value[0] > 'H')
        return (FALSE);
    value[1] = line[1];
    if (value[1] < '1' || value[1] > '8')
        return (FALSE);
    return (TRUE);
}

static boolean_t check_linearity_and_length(const char begin[2],
                                            const char end[2],
                                            const int len)
{
    if (begin[0] != end[0] && begin[1] != end[1])
        return (FALSE);
    if (!(begin[0] - end[0]) && end[1] - begin[1] != len - 1)
        return (FALSE);
    if (!(begin[1] - end[1]) && end[0] - begin[0] != len - 1)
        return (FALSE);
    return (TRUE);
}

boolean_t treat_boat_line(ship_t *ship, char ** splitted_line)
{
    int len = my_arrlen((char **)splitted_line);

    if (len != 3 || my_strlen(splitted_line[0]) != 1
        || my_strlen(splitted_line[1]) != 2
        || my_strlen(splitted_line[2]) != 2)
        return (FALSE);
    ship->len = splitted_line[0][0] - 48;
    if (ship->len < 2 || ship->len > 5)
        return (FALSE);
    if (!fill_edges_coords(splitted_line[1], ship->begin))
        return (FALSE);
    if (!fill_edges_coords(splitted_line[2], ship->end))
        return (FALSE);
    if (!check_linearity_and_length(ship->begin, ship->end, ship->len))
        return (FALSE);
    return (TRUE);
}
