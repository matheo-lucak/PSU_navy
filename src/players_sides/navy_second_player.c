/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Second player side of the navy program
*/

#include "my.h"
#include "navy_connect.h"
#include "navy.h"

static boolean_t wait_enemy_connection(void)
{
    refresh_siginterpret();
    while (!co_info.is_connected && co_info.catched_signal != SIGUSR2);
    print_my_pid();
    if (kill(co_info.enemy_pid, SIGUSR2))
        return (FALSE);
    co_info.is_connected = FALSE;
    while (!co_info.is_connected && co_info.catched_signal != SIGUSR2);
    if (kill(co_info.enemy_pid, SIGUSR2))
        return (FALSE);
    co_info.catched_signal = UNDEFINED;
    my_putstr("successfully connected\n");
    return (TRUE);
}

static void setup_signal_connection(const int first_player_pid)
{
    co_info.enemy_pid = first_player_pid;
    co_info.sa.sa_handler = (void *)get_enemy_signal;
    co_info.sa.sa_flags = SA_SIGINFO;
}

int navy_second_player(const int first_player_pid, const char path_boats_pos[])
{
    viewed_map_t gameboards;

    if (!first_player_pid)
        return (ERROR);
    setup_signal_connection(first_player_pid);
    if (!create_gameboards(&gameboards, path_boats_pos))
        return (ERROR);
    if (kill(first_player_pid, SIGUSR2))
        return (ERROR);
    if (!wait_enemy_connection())
        return (ERROR);
    return (navy_game_actions(gameboards, 0));
}