/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** connection_info.h
*/

#ifndef CONNECTION_INFO_H_

#define CONNECTION_INFO_H_


#include <signal.h>

#include "my_navy.h"


typedef struct connection_info_s {
    struct sigaction sa;
    boolean_t is_connected;
    __pid_t enemy_pid;
} connection_info_t;

connection_info_t co_info;

#endif /* CONNECTION_INFO_H_ */