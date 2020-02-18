/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** create_navy_base_from_file.c
*/

#include <stdlib.h>
#include "my.h"
#include "my_navy.h"

static void add_first_node(map_list_t **head)
{
    map_list_t *node = malloc(sizeof(map_list_t));

    if (!node)
        return;
    node->cell_coords = (point_t){0, 0};
    node->point_value = '.';
    node->next = NULL;
    *head = node;
}

map_list_t *create_navy_base_from_file(const char *pathway)
{
    map_list_t *navy_map = NULL;
    char *navy_map_coords = NULL;
    size_t index = 0;

    navy_map_coords = fill_navy_map_coords(pathway);
    while (index < 64) {
        if (!navy_map)
            add_first_node(&navy_map);
        else
            add_node();
        index += 1;
    }
}