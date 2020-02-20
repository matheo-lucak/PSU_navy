/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** navy_first_player.c
*/

#include "my.h"
#include "my_navy.h"

static void get_enemy_connection(const int sig_num, siginfo_t *info, void *vp)
{
    if (sig_num == SIGUSR2) {
        co_info.is_connected = TRUE;
        co_info.enemy_pid = info->si_pid;
    }
}

static boolean_t wait_enemy_connection(void)
{
    struct timespec ts = {0, 1000000000L};

    my_putstr("waiting for enemy connection...\n");
    while (!co_info.is_connected) {
        sigaction(SIGUSR1, &co_info.sa, NULL);
        nanosleep(&ts, NULL);
        sigaction(SIGUSR2, &co_info.sa, NULL);
        nanosleep(&ts, NULL);
    }
    if (kill(co_info.enemy_pid, SIGUSR2))
        return (FALSE);
    nanosleep(&ts, NULL);
    my_putstr("\nenemy connected\n");
    return (TRUE);
}

game_winner_t navy_first_player(const char path_boats_pos[])
{
    const __pid_t my_pid = getpid();
    viewed_map_t gameboards;

    co_info.is_connected = FALSE;
    if (!create_gameboards(&gameboards, path_boats_pos))
        return (ERROR);
    print_my_pid();
    co_info.sa.sa_handler = (void *)get_enemy_connection;
    co_info.sa.sa_flags = SA_SIGINFO;
    if (!wait_enemy_connection())
        return (ERROR);
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