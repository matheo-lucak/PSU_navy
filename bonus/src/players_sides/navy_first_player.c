/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** First player side of the Navy program.
*/

#include <unistd.h>
#include "my.h"
#include "navy_connect.h"
#include "navy.h"

SOCKET create_socket(void)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    write(2, "Creating socket ...\n", 20);
    if (sock == INVALID_SOCKET) {
        write(2, "Invalid socket !\n", 17);
        return (0);
    }
    write(2, "Socket created !\n", 17);
    return (sock);
}

SOCKADDR_IN create_serv_interface(SOCKET sock, short port)
{
    SOCKADDR_IN sin = {0};

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (SOCKADDR *) &sin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        write(2, "Error on bind\n", 14);
        exit(84);
    }
    my_printf("Port : %d\n", ntohs(sin.sin_port));
    return (sin);
}

void new_client(SOCKET *clients_sock, SOCKADDR_IN *clients_sin,
                    SOCKET sock)
{
    SOCKADDR_IN clients = {0};
    int sin_size = sizeof(clients);

    if (!clients_sock || !clients_sin)
        return ;
    *clients_sin = clients;
    write(2, "Waiting for client ...\n", 23);
    *clients_sock = accept(sock, (SOCKADDR *)clients_sin, &sin_size);
    if (*clients_sock == SOCKET_ERROR) {
        write(2, "Invalid socket !\n", 17);
        return ;
    }
    write(2, "Client connected !\n", 19);
}

int navy_first_player(const char path_boats_pos[])
{
    viewed_map_t gameboards;
    SOCKET sock = create_socket();
    SOCKET clients_sock;
    SOCKADDR_IN sin = create_serv_interface(sock, 8000);
    SOCKADDR_IN clients_sin;
    int sinsize = sizeof(clients_sin);

    if (listen(sock, 1) == SOCKET_ERROR) {
        write(2, "Too many connexions !\n", 22);
        return (1);
    }
    clients_sock = accept(sock, (SOCKADDR *)&clients_sin, &sinsize);
    if (clients_sock == INVALID_SOCKET) {
        write(2, "Couldn't accept connection\n", 27);
        return (1);
    }
    if (!create_gameboards(&gameboards, path_boats_pos))
        return (ERROR);
    return (navy_game_actions(clients_sock, gameboards, 1));
}