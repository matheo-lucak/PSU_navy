/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** game_actions.c
*/
#include "my.h"
#include "connection_info.h"

static int game_state(const char ally_map[65], const boolean_t play_first)
{
    co_info.is_connected = FALSE;
    if (!play_first) {
        while (!co_info.is_connected);
        if (co_info.catched_signal == SIGUSR2)
            return (CURRENT_PLAYER);
    }
    usleep(10000);
    if (is_map_still_up(ally_map))
        kill(co_info.enemy_pid, SIGUSR1);
    else {
        kill(co_info.enemy_pid, SIGUSR2);
        return (ENEMY_PLAYER);
    }
    if (play_first) {
        while (!co_info.is_connected);
        if (co_info.catched_signal == SIGUSR2)
            return (CURRENT_PLAYER);
    }
    co_info.is_connected = FALSE;
    return (UNDEFINED);
}

static void evaluate_enemy_attack(char ally_map[65])
{
    binary_signal_t binary_bridge = {0};
    boolean_t hit_or_missed = FALSE;

    binary_bridge = get_enemy_attack();
    my_printf("%c%c: ", binary_bridge.bridge % 8 + 'A',
                        binary_bridge.bridge / 8 + '1');
    hit_or_missed = update_map(ally_map, binary_bridge);
    if (!hit_or_missed)
        kill(co_info.enemy_pid, SIGUSR1);
    else    
        kill(co_info.enemy_pid, SIGUSR2);
    my_printf(hit_or_missed == TRUE ? "hit\n" : "missed\n");
}

static void evaluate_my_attack(char enemy_map[65])
{
    binary_signal_t target = {0};
    char *input = NULL;

    input = get_input();
    if (!input)
        return;
    target.bridge = 8 * (input[1] - '1') + input[0] - 'A';
    send_my_attack(target.bridge);
    while (!co_info.is_connected);
    co_info.is_connected = FALSE;
    if (co_info.catched_signal == SIGUSR1) {
        my_printf("%s: missed\n", input);
        enemy_map[target.bridge] = 'o';
    } else if (co_info.catched_signal == SIGUSR2) {
        my_printf("%s: hit\n", input);
        enemy_map[target.bridge] = 'x';
    }
}

static void attack_and_wait_enemy(viewed_map_t *gameboards,
                                const boolean_t play_first)
{
    if (!play_first)
        evaluate_enemy_attack(gameboards->ally_map);
    evaluate_my_attack(gameboards->enemy_map);
    if (play_first) {
        usleep(10000);
        evaluate_enemy_attack(gameboards->ally_map);
    }
}

int game_actions(viewed_map_t gameboards, const boolean_t play_first)
{
    int is_game_finished = UNDEFINED;

    print_gameboards(gameboards);
    do {
        attack_and_wait_enemy(&gameboards, play_first);
        print_gameboards(gameboards);
        is_game_finished = game_state(gameboards.ally_map, play_first);
    } while (is_game_finished == UNDEFINED);
    return (is_game_finished);
}