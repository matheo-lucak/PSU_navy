/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** my_navy.h
*/

#ifndef MY_NAVY_H_

#define MY_NAVY_H_

#include <unistd.h>

#include <time.h>
#include <signal.h>

typedef enum boolean_e {
    FALSE,
    TRUE
} boolean_t;

typedef enum is_attack_valid_e {
    VALID,
    WRONG,
    LEAVE
} is_attack_valid_t;

typedef enum game_winner_e {
    CURRENT_PLAYER = 0,
    ENEMY_PLAYER = 1,
    ERROR = 84
} game_winner_t;

typedef struct viewed_map_s {
    char ally_map[65];
    char enemy_map[65];
} viewed_map_t;

typedef struct ship_s {
    size_t len;
    char begin[2];
    char end[2];
} ship_t;

typedef struct connection_info_s {
    struct sigaction sa;
    boolean_t is_connected;
    __pid_t enemy_pid;
} connection_info_t;

connection_info_t co_info;

//Prints the navy usage of the program onto the stdout.
//
//Returns TRUE if could write.
//Returns FALSE otherwise.
boolean_t usage(void);


//Handles the game from the host side.
game_winner_t navy_first_player(const char path_boats_pos[]);


//Handles the game from the guest side.
game_winner_t navy_second_player(const __pid_t first_player_pid,
                                const char path_boats_pos[]);


//Prints ->    my pid: "pid"\n
void print_my_pid(void);

boolean_t create_gameboards(viewed_map_t *gameboards,
                            const char path_boats_pos[]);

boolean_t print_gameboards(viewed_map_t *gameboards);

boolean_t get_given_boats(char ally_map[65], const char path_boats_pos[]);

boolean_t treat_line(ship_t *ship, char * restrict * restrict splitted_line);

boolean_t check_boats_lengths(const char boats_lengths[4], const size_t len);

boolean_t check_too_many_chars(const int fd);

is_attack_valid_t get_attack(char *input);

is_attack_valid_t check_attack_error(char *input);

#endif /* MY_NAVY_H_ */