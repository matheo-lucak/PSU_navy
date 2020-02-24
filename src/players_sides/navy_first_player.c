/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** First player side of the Navy program.
*/

#include <unistd.h>
#include "my.h"
#include "navy_connect.h"
#include "navy.h"

static boolean_t wait_enemy_connection(void)
{
    my_putstr("waiting for enemy connection...\n");
    refresh_siginterpret();
    while (!co_info.is_connected);
    if (kill(co_info.enemy_pid, SIGUSR2))
        return (FALSE);
    co_info.sa.sa_handler = (void *)get_enemy_signal;
    refresh_siginterpret();
    while (!co_info.is_connected && co_info.catched_signal != SIGUSR2);
    if (kill(co_info.enemy_pid, SIGUSR2))
        return (FALSE);
    co_info.catched_signal = UNDEFINED;
    my_putstr("\nenemy connected\n");
    return (TRUE);
}

static void setup_signal_connection(void)
{
    co_info.sa.sa_handler = (void *)get_enemy_pid;
    co_info.sa.sa_flags = SA_SIGINFO;
}

int navy_first_player(const char path_boats_pos[])
{
    const int my_pid = getpid();
    viewed_map_t gameboards;

    setup_signal_connection();
    if (!create_gameboards(&gameboards, path_boats_pos))
        return (ERROR);
    print_my_pid();
    if (!wait_enemy_connection())
        return (ERROR);
    return (navy_game_actions(gameboards, 1));
}