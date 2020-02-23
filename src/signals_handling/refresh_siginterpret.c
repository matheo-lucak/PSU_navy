/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** refresh_siginterpret.c
*/

#include <stddef.h>
#include "connection_info.h"

void refresh_siginterpret(void)
{
    co_info.is_connected = FALSE;
    co_info.catched_signal = UNDEFINED;
    sigaction(SIGUSR1, &co_info.sa, NULL);
    sigaction(SIGUSR2, &co_info.sa, NULL);
}