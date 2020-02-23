/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** get_and_send_attacks.c
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "connection_info.h"

static is_attack_valid_t check_attack_error(char **input)
{
    if (!(*input))
        return (LEAVE);
    if (my_strlen(*input) != 2 || (*input)[0] < 'A' || (*input)[0] > 'H'
        || (*input)[1] < '1' || (*input)[1] > '8') {
        free(*input);
        return (WRONG);
    }
    return (VALID);
}

char *get_input(void)
{
    is_attack_valid_t input_validity = VALID;
    char *input = NULL;

    do {
        my_putstr("\nattack: ");
        input = get_next_line(0);
        input_validity = check_attack_error(&input);
        if (input_validity == LEAVE)
            return (NULL);
        if (input_validity == WRONG)
            my_putstr("wrong position");
    } while (input_validity != VALID);
    return (input);
}

binary_signal_t get_enemy_attack(void)
{
    binary_signal_t binary_bridge = {0};
    boolean_t received_signal = 0;
    register int index = 0;

    my_putstr("\nwaiting for enemy's attack...\n");
    while (index < 6) {
        co_info.is_connected = FALSE;
        while (!co_info.is_connected);
        binary_bridge.bridge |= ((co_info.catched_signal / 6) - 1);
        index += 1;
        if (index < 6)
            binary_bridge.bridge <<= 1;
    }
    return (binary_bridge);
}

void send_my_attack(const int nb)
{
    binary_signal_t bin_signal = {nb};
    register int index = 0;

    while (index < 6) {
        if (bin_signal.bridge & 32)
            kill(co_info.enemy_pid, SIGUSR2);
        else
            kill(co_info.enemy_pid, SIGUSR1);
        usleep(10000);
        bin_signal.bridge <<= 1;
        index += 1;
    }
}
