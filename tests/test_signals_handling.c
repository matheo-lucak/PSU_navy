/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** tests the signal_handling file functions
*/

#include <criterion/criterion.h>
#include "navy_connect.h"

Test(get_enemy_pid, get_first_ping)
{
    siginfo_t info;
    void *vp;

    co_info.is_connected = FALSE;
    co_info.enemy_pid = 0;
    info.si_pid = 3000;
    get_enemy_pid(SIGUSR2, &info, vp);
    if (co_info.enemy_pid == 3000 && co_info.is_connected == TRUE)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
}

Test(get_enemy_pid, false_signal)
{
    siginfo_t info;
    void *vp;

    co_info.is_connected = FALSE;
    co_info.enemy_pid = 0;
    info.si_pid = 3000;
    get_enemy_pid(SIGUSR1, &info, vp);
    if (co_info.enemy_pid == 0 && co_info.is_connected == FALSE)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
}

Test(get_enemy_signal, interpret_simple_sigusers)
{
    siginfo_t info;
    void *vp;

    co_info.is_connected = FALSE;
    co_info.enemy_pid = 3000;
    co_info.catched_signal = UNDEFINED;
    info.si_pid = 3000;
    get_enemy_signal(SIGUSR1, &info, vp);
    if (co_info.is_connected == TRUE && co_info.catched_signal == SIGUSR1)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
    co_info.is_connected = FALSE;
    co_info.catched_signal = UNDEFINED;
    get_enemy_signal(SIGUSR2, &info, vp);
    if (co_info.is_connected == TRUE && co_info.catched_signal == SIGUSR2)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
}

Test(get_enemy_signal, interpret_false_signals)
{
    siginfo_t info;
    void *vp;

    co_info.is_connected = FALSE;
    co_info.enemy_pid = 3000;
    co_info.catched_signal = UNDEFINED;
    info.si_pid = 2999;
    get_enemy_signal(SIGUSR1, &info, vp);
    if (co_info.is_connected == FALSE && co_info.catched_signal == UNDEFINED)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
    co_info.is_connected = FALSE;
    co_info.catched_signal = UNDEFINED;
    get_enemy_signal(UNDEFINED, &info, vp);
    if (co_info.is_connected == FALSE && co_info.catched_signal == UNDEFINED)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
}

Test(refresh_siginterpret, simple_refresh)
{
    co_info.is_connected = TRUE;
    co_info.catched_signal = SIGUSR1;
    co_info.sa.sa_handler = (void *)get_enemy_signal;
    refresh_siginterpret();
    if (co_info.catched_signal == UNDEFINED && co_info.is_connected == FALSE)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 2);
}