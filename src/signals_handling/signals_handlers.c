/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Assigned functions to the sigaction() functions.
*/

#include "navy_connect.h"

void get_enemy_pid(const int sig_num, siginfo_t *info, void *vp)
{
    if (sig_num == SIGUSR2) {
        co_info.is_connected = TRUE;
        co_info.enemy_pid = info->si_pid;
    }
}

void get_enemy_signal(const int sig_num, siginfo_t *info, void *vp)
{
    if ((sig_num == SIGUSR1 || sig_num == SIGUSR2)
        && info->si_pid == co_info.enemy_pid) {
        co_info.is_connected = TRUE;
        co_info.catched_signal = sig_num;
    }
}