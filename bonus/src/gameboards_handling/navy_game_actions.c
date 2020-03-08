/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Steps out actions done turn by turn.
*/
#include "my.h"
#include "navy_connect.h"
#include "navy.h"

static void print_winner(const int winner)
{
    if (winner == CURRENT_PLAYER)
        my_putstr("\nI won\n\n");
    else if (winner == ENEMY_PLAYER)
        my_putstr("\nEnemy won\n\n");
}

static int game_state(SOCKET sock, const char ally_map[65], const boolean_t play_first)
{
    char signal_receiver = 0;
    if (!play_first) {
        read(sock, &signal_receiver, 1);
        if (signal_receiver == 1)
            return (CURRENT_PLAYER);
    }
    if (battleships_left(ally_map)) {
        signal_receiver = 0;
        write(sock, &signal_receiver, 1);
    } else {
        signal_receiver = 1;
        write(sock, &signal_receiver, 1);
        return (ENEMY_PLAYER);
    }
    if (play_first) {
        read(sock, &signal_receiver, 1);
        if (signal_receiver == 1)
            return (CURRENT_PLAYER);
    }
    return (UNDEFINED);
}

static boolean_t attack_and_wait_enemy(SOCKET sock, viewed_map_t *gameboards,
                                        const boolean_t play_first,
                                        int *is_game_finished)
{
    if (!play_first) {
        if (!evaluate_enemy_attack(sock, gameboards->ally_map))
            return (FALSE);
        *is_game_finished = game_state(sock, gameboards->ally_map, play_first);
        if ((*is_game_finished) != UNDEFINED)
            return (TRUE);
    }
    if (!evaluate_my_attack(sock, gameboards->enemy_map))
        return (FALSE);
    if (play_first) {
        *is_game_finished = game_state(sock, gameboards->ally_map, play_first);
        if ((*is_game_finished) != UNDEFINED)
            return (TRUE);
        if (!evaluate_enemy_attack(sock, gameboards->ally_map))
            return (FALSE);
    }
    return (TRUE);
}

int navy_game_actions(SOCKET sock, viewed_map_t gameboards, const boolean_t play_first)
{
    int is_game_finished = UNDEFINED;
    int attack_state = UNDEFINED;

    print_gameboards(gameboards);
    do {
        attack_state = attack_and_wait_enemy(sock, &gameboards, play_first,
                                            &is_game_finished);
            if (!attack_state)
            return (LEAVE);
        print_gameboards(gameboards);
        if (is_game_finished != UNDEFINED)
            break;
        is_game_finished = game_state(sock, gameboards.ally_map, play_first);
    } while (is_game_finished == UNDEFINED);
    print_winner(is_game_finished);
    return (is_game_finished);
}