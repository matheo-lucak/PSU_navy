/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Refreshes the sigactions and the global variables.
*/

#include <stddef.h>
#include "navy_connect.h"

void refresh_siginterpret(void)
{
    co_info.is_connected = FALSE;
    co_info.catched_signal = UNDEFINED;
    sigaction(SIGUSR1, &co_info.sa, NULL);
    sigaction(SIGUSR2, &co_info.sa, NULL);
}