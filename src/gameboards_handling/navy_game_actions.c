/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Steps out actions done turn by turn.
*/
#include "my.h"
#include "navy_connect.h"
#include "navy.h"

static int game_state(const char ally_map[65], const boolean_t play_first)
{
    co_info.is_connected = FALSE;
    if (!play_first) {
        while (!co_info.is_connected);
        if (co_info.catched_signal == SIGUSR2)
            return (CURRENT_PLAYER);
    }
    usleep(10000);
    if (battleships_left(ally_map))
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

static boolean_t evaluate_enemy_attack(char ally_map[65])
{
    binary_signal_t binary_bridge = {0};
    boolean_t hit_or_missed = FALSE;

    if (!get_enemy_attack(&binary_bridge))
        return (FALSE);
    my_printf("%c%c: ", binary_bridge.bridge % 8 + 'A',
                        binary_bridge.bridge / 8 + '1');
    hit_or_missed = update_map(ally_map, binary_bridge);
    if (!hit_or_missed)
        kill(co_info.enemy_pid, SIGUSR1);
    else    
        kill(co_info.enemy_pid, SIGUSR2);
    my_printf(hit_or_missed == TRUE ? "hit\n" : "missed\n");
    return (TRUE);
}

static boolean_t evaluate_my_attack(char enemy_map[65])
{
    binary_signal_t target = {0};
    char *input = NULL;

    input = get_input();
    if (!input) {
        kill(co_info.enemy_pid, SIGUSR1);
        return (FALSE);
    }
    kill(co_info.enemy_pid, SIGUSR2);
    usleep(5000);
    target.bridge = get_target_aim(input[0], input[1]);
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
    return (TRUE);
}

static boolean_t attack_and_wait_enemy(viewed_map_t *gameboards,
                                const boolean_t play_first)
{
    if (!play_first) {
        if (!evaluate_enemy_attack(gameboards->ally_map))
            return (FALSE);
    }
    if (!evaluate_my_attack(gameboards->enemy_map))
        return (FALSE);
    if (play_first) {
        usleep(10000);
        if (!evaluate_enemy_attack(gameboards->ally_map))
            return (FALSE);
    }
    return (TRUE);
}

int navy_game_actions(viewed_map_t gameboards, const boolean_t play_first)
{
    int is_game_finished = UNDEFINED;

    print_gameboards(gameboards);
    do {
        if (!attack_and_wait_enemy(&gameboards, play_first))
            return (LEAVE);
        print_gameboards(gameboards);
        is_game_finished = game_state(gameboards.ally_map, play_first);
    } while (is_game_finished == UNDEFINED);
    if (is_game_finished == CURRENT_PLAYER)
        my_putstr("\nI won\n\n");
    else if (is_game_finished == ENEMY_PLAYER)
        my_putstr("\nEnemy won\n\n");
    return (is_game_finished);
}