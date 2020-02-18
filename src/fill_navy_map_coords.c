/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** fill_navy_map_coords.c
*/

#include <fcntl.h>
#include <stdlib.h>
#include "my.h"
#include "my_navy.h"

static boolean_t setup_map_coords(char **map_coords)
{
    *map_coords = malloc(sizeof(char) * 65);
    if (!(*map_coords))
        return (FALSE);
    my_memset(*map_coords, '.', 64);
    (*map_coords)[64] = '\0';
    return (TRUE);
}

char *fill_navy_map_coords(const char *pathway)
{
    const int fd = open(pathway, O_RDONLY);
    char *map_coords = NULL;

    if (fd == -1)
        return (NULL);
    if (!setup_map_coords(&map_coords))
        return (NULL);
    if (!get_given_boats(&map_coords, fd))
        return (NULL);
    close(fd);
    return (map_coords);
}