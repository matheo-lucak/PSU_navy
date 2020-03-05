/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Gets attack input and sends attacks.
*/

#include <unistd.h>
#include "my.h"
#include "navy_connect.h"

boolean_t get_enemy_attack(binary_signal_t *bridger)
{
    binary_signal_t binary_bridge = {0};
    boolean_t received_signal = 0;
    int index = 0;

    my_putstr("\nwaiting for enemy's attack...\n");
    co_info.is_connected = FALSE;
    while (!co_info.is_connected);
    if (co_info.catched_signal == SIGUSR1)
        return (FALSE);
    while (index < 6) {
        co_info.is_connected = FALSE;
        while (!co_info.is_connected);
        bridger->bridge |= ((co_info.catched_signal / 6) - 1);
        index += 1;
        if (index < 6)
            bridger->bridge <<= 1;
    }
    return (TRUE);
}

static boolean_t send_binary_code(const binary_signal_t bin_signal)
{
    if (bin_signal.bridge & 32) {
        if (kill(co_info.enemy_pid, SIGUSR2))
            return (FALSE);
    } else {
        if (kill(co_info.enemy_pid, SIGUSR1))
            return (FALSE);
    }
    usleep(20000);
    return (TRUE);
}

boolean_t send_my_attack(const int nb)
{
    binary_signal_t bin_signal = {nb};
    register int index = 0;

    while (index < 6) {
        if (!send_binary_code(bin_signal))
            return (FALSE);
        bin_signal.bridge <<= 1;
        index += 1;
    }
    return (TRUE);
}
