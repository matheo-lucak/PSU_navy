/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** tests the battleships_left function
*/

#include <criterion/criterion.h>
#include "navy.h"

Test(battleships_left, a_battleship_is_still_up)
{
    viewed_map_t gameboards;

    create_gameboards(&gameboards, "tests/test_files/correct_simple_one");
    if (battleships_left(gameboards.ally_map))
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
}

Test(battleships_left, no_battleship_left)
{
    if (!battleships_left("........"
                        "....o.x."
                        "......x."
                        ".xxxx.x."
                        "......x."
                        "..o...x."
                        "...o..xx"
                        ".....xxx"))
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
}