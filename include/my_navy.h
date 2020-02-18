/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** my_navy.h
*/

#ifndef MY_NAVY_H_

#define MY_NAVY_H_

#include <unistd.h>

typedef enum boolean_e {
    FALSE,
    TRUE
} boolean_t;

typedef enum game_winner_e {
    CURRENT_PLAYER = 0,
    ENEMY_PLAYER = 1,
    ERROR = 84
} game_winner_t;

typedef struct point_s {
    size_t x;
    size_t y;
} point_t;

typedef struct map_list_s {
    point_t cell_coords;
    char point_value;
    struct map_list_s *next;
} map_list_t;



boolean_t usage(void);



game_winner_t navy_first_player(const char *path_my_pos);



game_winner_t navy_second_player(const __pid_t first_player_pid,
                                const char *path_my_pos);



void print_my_pid(const __pid_t pid);

boolean_t get_given_boats(char **map_coords, const int fd);

#endif /* MY_NAVY_H_ */