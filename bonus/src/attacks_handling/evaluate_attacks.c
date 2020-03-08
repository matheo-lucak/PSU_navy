/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Evaluates both players attacks
*/

#include <stdlib.h>
#include "my.h"
#include "navy_connect.h"
#include "navy.h"

boolean_t evaluate_enemy_attack(SOCKET sock, char ally_map[65])
    {
    char pos = 0;
    boolean_t hit_or_missed = FALSE;

    if (!get_enemy_attack(sock, &pos))
        return (FALSE);
    my_printf("%c%c: ", pos % 8 + 'A',
                        pos / 8 + '1');
    hit_or_missed = update_map(ally_map, pos);
    if (write(sock, &hit_or_missed, 1) == -1)
        return (FALSE);
    my_printf(hit_or_missed == TRUE ? "hit\n" : "missed\n");
    return (TRUE);
}

static boolean_t check_input(char *input, SOCKET sock)
{
    char boolean = 0;

    if (!input) {
        write(sock, &boolean, 1);
        return (FALSE);
    }
    boolean = 1;
    write(sock, &boolean, 1);
    usleep(5000);
    return (TRUE);
}

static void assert_hit_or_missed(SOCKET sock, const char pos,
                                char *input, char enemy_map[65])
{
    char signal_receiver = 0;

    read(sock, &signal_receiver, 1);
    if (!signal_receiver) {
        my_printf("%s: missed\n", input);
        if (enemy_map[pos] != 'x')
            enemy_map[pos] = 'o';
    } else if (signal_receiver == 1) {
        my_printf("%s: hit\n", input);
        enemy_map[pos] = 'x';
    }
    if (input)
        free(input);
}

boolean_t evaluate_my_attack(SOCKET sock, char enemy_map[65])
{
    char pos = 0;
    char *input = NULL;

    input = get_input();
    pos = get_target_aim(input[0], input[1]);
    if (!send_my_attack(sock, pos))
        return (FALSE);
    assert_hit_or_missed(sock, pos, input, enemy_map);
    return (TRUE);
}