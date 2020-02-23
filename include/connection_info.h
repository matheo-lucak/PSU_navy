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

typedef struct binary_signal_s {
    unsigned int bridge : 6;
} binary_signal_t;


typedef struct connection_info_s {
    struct sigaction sa;
    boolean_t is_connected;
    int catched_signal;
    int enemy_pid;
} connection_info_t;

connection_info_t co_info;

void get_enemy_pid(const int sig_num, siginfo_t *info, void *vp);

void get_enemy_signal(const int sig_num, siginfo_t *info, void *vp);

void refresh_siginterpret(void);

#endif /* CONNECTION_INFO_H_ */