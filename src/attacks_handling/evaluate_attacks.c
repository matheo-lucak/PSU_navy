/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Evaluates both players attacks
*/

#include <stdlib.h>
#include "my.h"
#include "navy_connect.h"
#include "navy.h"

boolean_t evaluate_enemy_attack(char ally_map[65])
{
    binary_signal_t binary_bridge = {0};
    boolean_t hit_or_missed = FALSE;

    if (!get_enemy_attack(&binary_bridge))
        return (FALSE);
    my_printf("%c%c: ", binary_bridge.bridge % 8 + 'A',
                        binary_bridge.bridge / 8 + '1');
    hit_or_missed = update_map(ally_map, binary_bridge);
    if (!hit_or_missed) {
        if (kill(co_info.enemy_pid, SIGUSR1))
            return (FALSE);
    } else {
        if (kill(co_info.enemy_pid, SIGUSR2))
            return (FALSE);
    }
    my_printf(hit_or_missed == TRUE ? "hit\n" : "missed\n");
    return (TRUE);
}

static boolean_t check_input(char *input)
{
    if (!input) {
        kill(co_info.enemy_pid, SIGUSR1);
        return (FALSE);
    }
    if (kill(co_info.enemy_pid, SIGUSR2))
        return (FALSE);
    usleep(5000);
    return (TRUE);
}

static void assert_hit_or_missed(const binary_signal_t target,
                                char *input, char enemy_map[65])
{
    if (co_info.catched_signal == SIGUSR1) {
        my_printf("%s: missed\n", input);
        if (enemy_map[target.bridge] != 'x')
            enemy_map[target.bridge] = 'o';
    } else if (co_info.catched_signal == SIGUSR2) {
        my_printf("%s: hit\n", input);
        enemy_map[target.bridge] = 'x';
    }
    if (input)
        free(input);
}

boolean_t evaluate_my_attack(char enemy_map[65])
{
    binary_signal_t target = {0};
    char *input = NULL;

    input = get_input();
    if (!check_input(input))
        return (FALSE);
    target.bridge = get_target_aim(input[0], input[1]);
    if (!send_my_attack(target.bridge))
        return (FALSE);
    while (!co_info.is_connected);
    co_info.is_connected = FALSE;
    assert_hit_or_missed(target, input, enemy_map);
    return (TRUE);
}