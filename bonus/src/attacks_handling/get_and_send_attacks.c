/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Gets attack input and sends attacks.
*/

#include <unistd.h>
#include "my.h"
#include "navy_connect.h"

boolean_t get_enemy_attack(SOCKET sock, char *pos)
{
    char signal_receiver = 0;
    int index = 0;

    my_putstr("\nwaiting for enemy's attack...\n");
    if (read(sock, &signal_receiver, 1) == -1)
        return (FALSE);
    *pos = signal_receiver;
    return (TRUE);
}

boolean_t send_my_attack(SOCKET sock, const int nb)
{
    char signal_receiver = nb;

    if (write(sock, &signal_receiver, 1) == -1) {
        return (FALSE);
    }
    return (TRUE);
}
