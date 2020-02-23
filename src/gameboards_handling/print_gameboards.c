/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** print_gameboards.c
*/

#include "my.h"
#include "my_navy.h"

void print_map(const char *map)
{
    register size_t index = 1;
    register size_t i = 0;

    my_putstr(" |A B C D E F G H\n");
    my_putstr("-+---------------\n");
    while (index <= 8) {
        my_printf("%lu|%c %c %c %c %c %c %c %c\n", index,
                    map[i], map[i + 1], map[i + 2], map[i + 3],
                    map[i + 4], map[i + 5], map[i + 6], map[i + 7]);
        index += 1;
        i += 8;
    }
}

boolean_t print_gameboards(viewed_map_t *gameboards)
{
    if (my_strlen(gameboards->ally_map) != 64 ||
        my_strlen(gameboards->enemy_map) != 64)
        return (FALSE);
    my_putstr("\nmy positions:\n");
    print_map(gameboards->ally_map);
    my_putstr("\nenemy's positions:\n");
    print_map(gameboards->enemy_map);
}