/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** print_my_pid.c
*/

#include <unistd.h>
#include "my.h"

void print_my_pid(const __pid_t pid)
{
    my_printf("my pid: %d\n", pid);
}