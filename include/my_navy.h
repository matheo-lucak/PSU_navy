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

typedef struct viewed_map_s {
    char ally_map[65];
    char enemy_map[65];
} viewed_map_t;

typedef struct connection_info_s {
    __pid_t enemy_pid;
} connection_info_t;

//Prints the navy usage of the program onto the stdout.
//
//Returns TRUE if could write.
//Returns FALSE otherwise.
boolean_t usage(void);



game_winner_t navy_first_player(const char *path_my_pos);



game_winner_t navy_second_player(const __pid_t first_player_pid,
                                const char *path_my_pos);



void print_my_pid(const __pid_t pid);

boolean_t get_given_boats(char **map_coords, const int fd);

viewed_map_t create_gameboards(const char path_boats_pos[]);

boolean_t print_gameboards(viewed_map_t *gameboards);

#endif /* MY_NAVY_H_ */