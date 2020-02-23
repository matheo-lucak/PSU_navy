/*
** EPITECH PROJECT, 2020
** PSU_navy_2019
** File description:
** game_actions
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "connection_info.h"

static binary_signal_t receive_signal(void)
{
    binary_signal_t binary_bridge = {0};
    boolean_t received_signal = 0;
    int index = 0;

    while (index < 6) {
        co_info.is_connected = FALSE;
        while (!co_info.is_connected);
        binary_bridge.bridge |= co_info.catched_signal;
        binary_bridge.bridge <<= 1;
        index += 1;
    }
    return (binary_bridge);
}

static void send_signal(const int nb)
{
    binary_signal_t bin_signal = {nb};
    int index = 0;

    while (index < 6) {
        if (bin_signal.bridge & 32)
            kill(co_info.enemy_pid, SIGUSR2);
        else
            kill(co_info.enemy_pid, SIGUSR1);
        usleep(100000);
        bin_signal.bridge <<= 1;
        index += 1;
    }
}

is_attack_valid_t get_input(char **input)
{
    is_attack_valid_t input_validity = VALID;

    do {
        input_validity = get_attack(&input);
        if (input_validity == LEAVE)
            return (LEAVE_GAME);
    } while (input_validity != VALID);
    return (input_validity);
}

void update_ally_map(viewed_map_t *gameboards, binary_signal_t binary_bridge)
{
    if ((gameboards->ally_map[binary_bridge.bridge] >= '2' &&
        gameboards->ally_map[binary_bridge.bridge] >= '5') ||
        gameboards->ally_map[binary_bridge.bridge] == 'x') {
        gameboards->ally_map[binary_bridge.bridge] = 'x';
        kill(co_info.enemy_pid, SIGUSR2);
    } else {
        gameboards->ally_map[binary_bridge.bridge] = 'o';
        kill(co_info.enemy_pid, SIGUSR1);
    }
}

void update_ennemy_map(viewed_map_t *gameboards, binary_signal_t binary_bridge)
{
    while (!co_info.is_connected);
    if (co_info.catched_signal == SIGUSR2) {
        my_putstr(": hit\n");
        gameboards->ally_map[binary_bridge.bridge] = 'x';
    } else if (co_info.catched_signal == SIGUSR1) {
        my_putstr(": missed\n");
        gameboards->ally_map[binary_bridge.bridge] = 'o';
    }
}

void update_gameboard(viewed_map_t *gameboards, binary_signal_t binary_bridge,
                                                    const boolean_t play_first)
{
    static const void (*update_map[2])(viewed_map_t *, binary_signal_t) = {
        update_ally_map,
        update_ennemy_map
    };
    update_map[play_first](gameboards, binary_bridge);
    update_map[(play_first + 1 % 2)](gameboards, binary_bridge);
}

game_winner_t game_loop(viewed_map_t gameboards, const boolean_t play_first)
{
    binary_signal_t binary_bridge = {0};
    is_attack_valid_t input_validity = VALID;
    game_winner_t winner = CURRENT_PLAYER;
    char *input = NULL;

    co_info.sa.sa_handler = (void *)get_enemy_signal;
    if (!play_first)
        binary_bridge = receive_signal();
    do {
        if (get_attack(&input) == LEAVE)
            return (LEAVE);
        send_signal(((input[1] - 1) * 8) + input[0] - 'A');
        binary_bridge = receive_signal();
        update_gameboard(&gameboards, binary_bridge, play_first);
        winner = did_someone_win(gameboards);
    } while (winner);
    return (winner);
}