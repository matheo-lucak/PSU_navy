/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** attack.c
*/

#include "my.h"
#include "my_navy.h"

is_attack_valid_t get_attack(char *input)
{
    my_putstr("attack: ");
    input = get_next_line(0);
    if (!input)
        return (LEAVE);
    if (my_strlen(input) != 2) {
        free(input);
        return (WRONG);
    }
    if (input[0] < 'A' || input[0] > 'H') {
        free(input);
        return (WRONG);
    }
    if (input[0] < '1' || input[0] > '8') {
        free(input);
        return (WRONG);
    }
    return (TRUE);
}