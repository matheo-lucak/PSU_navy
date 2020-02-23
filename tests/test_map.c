/*
** EPITECH PROJECT, 2020
** PSU_navy_2019
** File description:
** test_map
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my_navy.h"
#include "my.h"

Test(usage, print_blank_map)
{
    char *map = malloc(sizeof(char) * (65));
    char correct_map[] = " |A B C D E F G H\n"\
                        "-+---------------\n"\
                        "1|. . . . . . . .\n"\
                        "2|. . . . . . . .\n"\
                        "3|. . . . . . . .\n"\
                        "4|. . . . . . . .\n"\
                        "5|. . . . . . . .\n"\
                        "6|. . . . . . . .\n"\
                        "7|. . . . . . . .\n"\
                        "8|. . . . . . . .\n";
    my_memset(map, '.', 64);
    print_map(map);
    cr_redirect_stdout();
    cr_assert_stdout_eq(correct_map);
}