/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** navy_first_player.c
*/

#include "my.h"
#include "my_navy.h"

game_winner_t navy_first_player(const char *path_my_pos)
{
    const __pid_t my_pid = getpid();

    print_my_pid(my_pid);
    my_putstr("\nwaiting for enemy connection...\n");
    while (1);
    return (CURRENT_PLAYER);
}

// my positions:
//  |A B C D E F G H
// -+---------------
// 1|. . . 2 . . . .
// 2|. . . 2 . . . .
// 3|. . . . . . . .
// 4|3 3 3 . . . . .
// 5|. . 4 . . . . .
// 6|. . 4 5 5 5 5 5
// 7|. . 4 . . . . .
// 8|. . 4 . . . . .