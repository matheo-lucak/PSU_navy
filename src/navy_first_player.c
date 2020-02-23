/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** navy_first_player.c
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

static boolean_t wait_enemy_connection(void)
{
    my_putstr("waiting for enemy connection...\n");
    sigaction(SIGUSR1, &co_info.sa, NULL);
    sigaction(SIGUSR2, &co_info.sa, NULL);
    while (!co_info.is_connected);
    if (kill(co_info.enemy_pid, SIGUSR2))
        return (FALSE);
    usleep(100000);
    my_putstr("\nenemy connected\n");
    return (TRUE);
}

static void setup_signal_connection(void)
{
    co_info.is_connected = FALSE;
    co_info.sa.sa_handler = (void *)get_enemy_connection;
    co_info.sa.sa_flags = SA_SIGINFO;
}

game_winner_t navy_first_player(const char path_boats_pos[])
{
    const int my_pid = getpid();
    viewed_map_t gameboards;

    setup_signal_connection();
    if (!create_gameboards(&gameboards, path_boats_pos))
        return (ERROR);
    print_my_pid();
    if (!wait_enemy_connection())
        return (ERROR);
    print_gameboards(&gameboards);
    return (CURRENT_PLAYER);
}