/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** navy_second_player.c
*/

#include <errno.h>
#include "my.h"
#include "my_navy.h"

static void get_enemy_connection(const int sig_num, siginfo_t *info, void *vp)
{
    if (sig_num == SIGUSR2) {
        co_info.is_connected = TRUE;
        co_info.enemy_pid = info->si_pid;
    }
}

static void wait_enemy_connection(void)
{
    struct timespec ts = {0, 1000000000L};

    co_info.sa.sa_handler = (void *)get_enemy_connection;
    co_info.sa.sa_flags = SA_SIGINFO;
    while (!co_info.is_connected) {
        sigaction(SIGUSR1, &co_info.sa, NULL);
        nanosleep(&ts, NULL);
        sigaction(SIGUSR2, &co_info.sa, NULL);
        nanosleep(&ts, NULL);
    }
    my_putstr("successfully connected\n");
}

game_winner_t navy_second_player(const __pid_t first_player_pid,
                                const char path_boats_pos[])
{
    struct timespec ts = {0, 1000000000L};
    viewed_map_t gameboards;

    if (!first_player_pid)
        return (ERROR);
    co_info.is_connected = FALSE;
    co_info.enemy_pid = first_player_pid;
    if (!create_gameboards(&gameboards, path_boats_pos))
        return (ERROR);
    if (kill(first_player_pid, SIGUSR2))
        return (ERROR);
    print_my_pid();
    nanosleep(&ts, NULL);
    wait_enemy_connection();
    print_gameboards(&gameboards);
    return (CURRENT_PLAYER);
}