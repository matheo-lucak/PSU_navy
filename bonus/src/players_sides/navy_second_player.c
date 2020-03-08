/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Second player side of the navy program
*/

#include "my.h"
#include "navy_connect.h"
#include "errno.h"
#include "navy.h"

SOCKADDR_IN create_client_interface(SOCKET sock, short port, const char *hostname)
{
    SOCKADDR_IN sin = {0};

    sin.sin_addr.s_addr = inet_addr(hostname);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    write(2, "Connexion ...\n", 13);
    if (connect(sock, (SOCKADDR *) &sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        perror("Error on connexion\n");
        exit(84);
    }
    return (sin);
}

int navy_second_player(const char *hostname, const char path_boats_pos[])
{
    viewed_map_t gameboards;
    SOCKET sock = create_socket();
    SOCKADDR_IN sin;

    sin = create_client_interface(sock, 8000, hostname);
    if (!create_gameboards(&gameboards, path_boats_pos))
        return (ERROR);
    return (navy_game_actions(sock, gameboards, 0));
}