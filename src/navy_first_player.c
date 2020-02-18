/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** navy_first_player.c
*/

#include <signal.h>
#include "my.h"
#include "my_navy.h"

boolean_t is_connected = FALSE;
__pid_t enemy_pid = 0;

static void get_enemy_connection(const int sig_num, siginfo_t *info, void *vp)
{ 
    if (sig_num == SIGUSR2) {
        is_connected = TRUE;
        enemy_pid = info->si_pid;
    }
}

static void check_for_enemy_connection()
{
    struct sigaction sa;

    sa.sa_handler = (void *)get_enemy_connection;
    sa.sa_flags = SA_SIGINFO;
    my_putstr("waiting for enemy connection...\n");
    while (!is_connected)
        sigaction(SIGUSR2, &sa, NULL);
}

game_winner_t navy_first_player(const char path_boats_pos[])
{
    const __pid_t my_pid = getpid();
    viewed_map_t gameboards;

    print_my_pid(my_pid);
    check_for_enemy_connection();
    gameboards = create_gameboards(path_boats_pos);
    print_gameboards(&gameboards);
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