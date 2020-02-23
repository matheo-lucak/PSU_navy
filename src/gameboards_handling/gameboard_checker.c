/*
** EPITECH PROJECT, 2020
** PSU_navy_2019
** File description:
** gameboard_checker
*/

#include "connection_info.h"

game_winner_t did_someone_win(viewed_map_t gameboards, const boolean_t first_player)
{
    int did_i_lost = SIGUSR2;  //SIGUSR1 if nothing. SIGUSR2 if win.
    int index = 0;

    if (!first_player) {
        co_info.is_connected = FALSE;
        while (!co_info.is_connected);
        if (co_info.catched_signal)
            return (CURRENT_PLAYER);
    }
    while (index < 64) {
        if (gameboards.ally_map[index] >= '2' && gameboards.ally_map[index] <= '5')
            did_i_lost = SIGUSR1;
        index += 1;
    }
    if (first_player) {
        kill(co_info.enemy_pid, did_i_lost);
    }
}