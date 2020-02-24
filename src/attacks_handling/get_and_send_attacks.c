/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Gets attack input and sends attacks.
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "navy_connect.h"

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
    is_attack_valid_t input_validity = WRONG;
    char *input = NULL;

    while (input_validity != VALID) {
        my_putstr("\nattack: ");
        input = get_next_line(0);
        input_validity = check_attack_error(&input);
        if (input_validity == LEAVE)
            return (NULL);
        if (input_validity == WRONG)
            my_putstr("wrong position");
    }
    return (input);
}

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
