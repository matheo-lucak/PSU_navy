/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Prints the usage of the navy program onto the stdout.
*/

#include "my.h"
#include "navy_def.h"

boolean_t usage(void)
{
    if (my_putstr("USAGE\n"
        "     ./navy [first_player_pid] navy_positions\n"
        "DESCRIPTION\n"
        "     first_player_pid: only for the 2nd player."
        "  pid of the first player.\n"
        "     navy_positions: file representing the"
        " positions of the ships.\n") == ERROR);
        return (FALSE);
    return (TRUE);
}