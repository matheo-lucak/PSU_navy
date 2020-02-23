/*
** EPITECH PROJECT, 2020
** PSU_navy_2019
** File description:
** test_attack
*/

#include <criterion/criterion.h>
#include "my_navy.h"
#include "my.h"

Test(usage, attack_error_leave)
{
    cr_assert(check_attack_error(NULL) == LEAVE);
}

Test(usage, attack_error_wrong_letter)
{
    char *str = my_strdup("Z1");
    cr_assert(check_attack_error(str) == WRONG);
}

Test(usage, attack_error_wrong_number)
{
    char *str = my_strdup("A9");
    cr_assert(check_attack_error(str) == WRONG);
}