/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** test_usage.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_navy.h"

Test(usage, print_usage)
{
    cr_redirect_stdout();
    usage();
    cr_assert_stdout_eq_str("USAGE\n"
    "     ./navy [first_player_pid] navy_positions\n"
    "DESCRIPTION\n"
    "     first_player_pid: only for the 2nd player."
    "  pid of the first player.\n"
    "     navy_positions: file representing the positions of the ships.\n");
}

Test(usage, check_usage_error)
{
    close(0);
    if (!usage())
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}