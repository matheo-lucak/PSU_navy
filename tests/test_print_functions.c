/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** tests the print_gameboards function
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"
#include "navy.h"

Test(print_gameboards, simple_print)
{
    viewed_map_t gameboards;

    cr_redirect_stdout();
    if (!create_gameboards(&gameboards, "tests/test_files/correct_simple_two"))
        cr_assert_eq(1, 2);
    if (!print_gameboards(gameboards))
        cr_assert_eq(1, 2);
    cr_assert_stdout_eq_str("\nmy positions:\n |A B C D E F G H\n"
                            "-+---------------\n1|2 3 4 5 . . . .\n"
                            "2|2 3 4 5 . . . .\n3|. 3 4 5 . . . .\n"
                            "4|. . 4 5 . . . .\n5|. . . 5 . . . .\n"
                            "6|. . . . . . . .\n7|. . . . . . . .\n"
                            "8|. . . . . . . .\n\nenemy's positions:\n"
                            " |A B C D E F G H\n-+---------------\n"
                            "1|. . . . . . . .\n2|. . . . . . . .\n"
                            "3|. . . . . . . .\n4|. . . . . . . .\n"
                            "5|. . . . . . . .\n6|. . . . . . . .\n"
                            "7|. . . . . . . .\n8|. . . . . . . .\n");
}

Test(print_gameboards, false_map_size)
{
    viewed_map_t gameboards;

    gameboards.ally_map[0] = 0;
    gameboards.enemy_map[0] = 0;
    cr_assert_eq(1, !print_gameboards(gameboards) ? 1 : 2);
    my_memset(gameboards.ally_map, '.', 64);
    gameboards.ally_map[64] = 0;
    gameboards.enemy_map[0] = 0;
    cr_assert_eq(1, !print_gameboards(gameboards) ? 1 : 2);
}