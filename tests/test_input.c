/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** tests the update_map function
*/

#include <criterion/criterion.h>
#include "navy_connect.h"
#include "navy.h"
#include "my.h"

Test(check_input, no_input)
{
    char *str = NULL;
    int input_validity = check_attack_error(str);

    cr_assert(input_validity == LEAVE);
}

Test(check_input, wrong_input_1)
{
    char *str = my_strdup("Z1");
    int input_validity = check_attack_error(str);

    cr_assert(input_validity == WRONG);
}

Test(check_input, wrong_input_2)
{
    char *str = my_strdup("A9");
    int input_validity = check_attack_error(str);

    cr_assert(input_validity == WRONG);
}

Test(check_input, valid_input)
{
    char *str = my_strdup("A1");
    int input_validity = check_attack_error(str);

    if (str)
        free(str);
    cr_assert(input_validity == VALID);
}

Test(check_input, wrong_get_next_line)
{
    char *input = NULL;

    close(0);
    input = get_input();
    cr_assert(!input);
}