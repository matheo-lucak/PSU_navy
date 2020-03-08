/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Gets a correct input
*/

#include <stdlib.h>
#include "my.h"
#include "navy.h"

int check_attack_error(char *input)
{
    if (!input)
        return (LEAVE);
    if (my_strlen(input) != 2 || input[0] < 'A' || input[0] > 'H'
        || input[1] < '1' || input[1] > '8') {
        free(input);
        return (WRONG);
    }
    return (VALID);
}

char *get_input(void)
{
    int input_validity = WRONG;
    char *input = NULL;

    while (input_validity != VALID) {
        my_putstr("\nattack: ");
        input = get_next_line(0);
        input_validity = check_attack_error(input);
        if (input_validity == LEAVE)
            return (NULL);
        if (input_validity == WRONG)
            my_putstr("wrong position");
    }
    return (input);
}