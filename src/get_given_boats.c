/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** get_given_boats.c
*/

#include "my.h"
#include "my_navy.h"

static boolean_t place_boats_in_map_coords(char **map_coords,
                                        char **boat_stats)
{
    char x_init = '\0';
    char x_end = '\0';
    int y_init = 0;
    int y_end = 0;
    int length = 0;

    if (my_arrlen(boat_stats) != 3 || my_strlen(boat_stats[0]) != 1
        || my_strlen(boat_stats[1]) != 2 || my_strlen(boat_stats[2]) != 2) {
        my_free_arr(boat_stats);
        return (FALSE);
    }
    length = my_absolute_getnbr(boat_stats[0]);
    if (length < 2 || length > 5)
        return (FALSE);
    x_init = boat_stats[1][0];
    if (x_init < 'A' || x_init > 'H')
        return (FALSE);
    y_init = my_absolute_getnbr(&(boat_stats[1][1]));
    if (y_init < 1 || y_init > 8)
        return (FALSE);
    x_end = boat_stats[2][0];
    if (x_end < 'A' || x_end > 'H')
        return (FALSE);
    y_end = my_absolute_getnbr(&(boat_stats[2][1]));
    if (y_end < 1 || y_end > 8)
        return (FALSE);
}

boolean_t get_given_boats(char **map_coords, const int fd)
{
    char **splitted_line = NULL;
    char *line_stock = NULL;
    size_t index = 0;

    while (index < 4) {
        splitted_line = my_str_to_word_array(get_next_line(fd, 10), ":", 1);
        if (!place_boats_in_map_coords(map_coords, splitted_line))
            return (FALSE);
        index += 1;
    }
    line_stock = get_next_line(fd, 10);
    if (line_stock) {
        free(line_stock);
        return (FALSE);
    }
    return (TRUE);
}