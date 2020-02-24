/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Main function of the navy program.
*/

#include "my.h"
#include "navy.h"

int main(const int ac, const char * const av[])
{
    if (ac != 2 && ac != 3) {
        usage();
        return (84);
    }
    if (ac == 2) {
        if (!my_strcmp(av[1], "-h", 0)) {
            usage();
            return (0);
        }
        return (navy_first_player(av[1]));
    }
    return (navy_second_player(my_absolute_getnbr(av[1]), av[2]));
}