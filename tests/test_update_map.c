/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** tests the update_map function
*/

#include <criterion/criterion.h>
#include "navy_connect.h"
#include "navy.h"

Test(update_map, hit_battleship)
{
    viewed_map_t gameboards;

    if (!create_gameboards(&gameboards, "tests/test_files/correct_simple_two"))
        cr_assert_eq(1, 2);
    if (update_map(gameboards.ally_map, (binary_signal_t){0}))
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
    cr_assert_str_eq(gameboards.ally_map, "x345...."
                                        "2345...."
                                        ".345...."
                                        "..45...."
                                        "...5...."
                                        "........"
                                        "........"
                                        "........");
}

Test(update_map, missed_battleship)
{
    viewed_map_t gameboards;

    if (!create_gameboards(&gameboards, "tests/test_files/correct_simple_two"))
        cr_assert_eq(1, 2);
    if (!update_map(gameboards.ally_map, (binary_signal_t){7}))
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
    cr_assert_str_eq(gameboards.ally_map, "2345...o"
                                        "2345...."
                                        ".345...."
                                        "..45...."
                                        "...5...."
                                        "........"
                                        "........"
                                        "........");
}

Test(update_map, double_hit_battleship)
{
    viewed_map_t gameboards;

    if (!create_gameboards(&gameboards, "tests/test_files/correct_simple_two"))
        cr_assert_eq(1, 2);
    if (update_map(gameboards.ally_map, (binary_signal_t){0}))
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
    if (update_map(gameboards.ally_map, (binary_signal_t){0}))
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
    cr_assert_str_eq(gameboards.ally_map, "x345...."
                                        "2345...."
                                        ".345...."
                                        "..45...."
                                        "...5...."
                                        "........"
                                        "........"
                                        "........");
}