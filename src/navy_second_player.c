/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** navy_second_player.c
*/

#include "my.h"
#include "connection_info.h"

static void get_enemy_connection(const int sig_num, siginfo_t *info, void *vp)
{
    if (sig_num == SIGUSR2) {
        co_info.is_connected = TRUE;
        co_info.enemy_pid = info->si_pid;
    }
}

static void wait_enemy_connection(void)
{
    sigaction(SIGUSR1, &co_info.sa, NULL);
    sigaction(SIGUSR2, &co_info.sa, NULL);
    while (!co_info.is_connected);
    my_putstr("successfully connected\n");
}

static void setup_signal_connection(const int first_player_pid)
{
    co_info.is_connected = FALSE;
    co_info.enemy_pid = first_player_pid;
    co_info.sa.sa_handler = (void *)wait_enemy_connection;
    co_info.sa.sa_flags = SA_SIGINFO;
}

game_winner_t navy_second_player(const int first_player_pid,
                                const char path_boats_pos[])
{
    viewed_map_t gameboards;

    if (!first_player_pid)
        return (ERROR);
    setup_signal_connection(first_player_pid);
    if (!create_gameboards(&gameboards, path_boats_pos))
        return (ERROR);
    print_my_pid();
    if (kill(first_player_pid, SIGUSR2))
        return (ERROR);
    wait_enemy_connection();
    print_gameboards(&gameboards);
    return (CURRENT_PLAYER);
}