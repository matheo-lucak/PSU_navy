/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** tests the create_gameboards function.
*/

#include <criterion/criterion.h>
#include "navy.h"

Test(create_gameboards, false_wrong_pathway)
{
    viewed_map_t gameboards;

    cr_assert_eq(1, !create_gameboards(&gameboards, "going_nowhere") ? 1 : 2);
}

Test(create_gameboards, false_multiple_correct_lengths)
{
    const char pathway[] = "tests/test_files/false_mul_correct_lengths";
    viewed_map_t gameboards;

    cr_assert_eq(1, !create_gameboards(&gameboards, pathway) ? 1 : 2);
}

Test(create_gameboards, false_coordinates)
{
    const char pathway[] = "tests/test_files/false_coordinates";
    viewed_map_t gameboards;

    cr_assert_eq(1, !create_gameboards(&gameboards, pathway) ? 1 : 2);
}

Test(create_gameboards, false_overlapping_battleships)
{
    const char pathway[] = "tests/test_files/false_overlapping_battleships";
    viewed_map_t gameboards;

    cr_assert_eq(1, !create_gameboards(&gameboards, pathway) ? 1 : 2);
}

Test(create_gameboards, false_too_many_characters)
{
    const char pathway[] = "tests/test_files/false_too_many_characters";
    viewed_map_t gameboards;

    cr_assert_eq(1, !create_gameboards(&gameboards, pathway) ? 1 : 2);
}