/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** tests the create_gameboards function.
*/

#include <criterion/criterion.h>
#include "navy.h"

Test(create_gameboards, correct_battleship_pos)
{
    viewed_map_t gameboards;

    if (!create_gameboards(&gameboards,
                        "tests/test_files/correct_simple_one"))
        cr_assert_eq(1, 2);
    cr_assert_str_eq(gameboards.ally_map, "22......333....."
                                        "4444....55555..."
                                        "................"
                                        "................");
    cr_assert_str_eq(gameboards.enemy_map, "................"
                                        "................"
                                        "................"
                                        "................");
}

Test(create_gameboards, wrong_pathway)
{
    viewed_map_t gameboards;

    if (!create_gameboards(&gameboards, "going_nowhere"))
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
}