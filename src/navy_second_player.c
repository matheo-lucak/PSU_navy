/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** navy_second_player.c
*/

#include "my_navy.h"

game_winner_t navy_second_player(const __pid_t first_player_pid,
                                const char *path_my_pos)
{
    if (!first_player_pid)
        return (ERROR);
    return (CURRENT_PLAYER);
}