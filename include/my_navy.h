/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** my_navy.h
*/

#ifndef MY_NAVY_H_

#define MY_NAVY_H_

#define UNDEFINED -1

typedef enum boolean_e {
    FALSE,
    TRUE
} boolean_t;


typedef enum is_attack_valid_e {
    LEAVE,
    VALID,
    WRONG
} is_attack_valid_t;


typedef enum game_winner_e {
    CURRENT_PLAYER = 0,
    ENEMY_PLAYER = 1,
    LEAVE_GAME = 0,
    ERROR = 84
} game_winner_t;


typedef struct viewed_map_s {
    char ally_map[65];
    char enemy_map[65];
} viewed_map_t;


typedef struct ship_s {
    int len;
    char begin[2];
    char end[2];
} ship_t;


/*
** ******************
** | Error Handlers |
** ******************
*/

//Prints the navy usage of the program onto the stdout.
//
//Returns TRUE if could write.
//Returns FALSE otherwise.
boolean_t usage(void);


/*
** ***********************************************************************
** | Different instances of the main program corresponding of the player |
** ***********************************************************************
*/

//Handles the game from the host side.
int navy_first_player(const char path_boats_pos[]);


//Handles the game from the guest side.
int navy_second_player(const int first_player_pid,
                        const char path_boats_pos[]);


/*
** ************************
** | Print-only functions |
** ************************
*/

//Prints:
//
//my pid: "pid"\n
void print_my_pid(void);


//Prints the ally and enemy gameboards.
boolean_t print_gameboards(viewed_map_t gameboards);


/*
** *****************
** | Maps Handling |
** *****************
*/

//Memsets both ally and enemy strings with '.'.
//
//Calls get_given_boats() and Returns FALSE if this function returns FALSE.
boolean_t create_gameboards(viewed_map_t *gameboards,
                            const char path_boats_pos[]);


boolean_t get_given_boats(char ally_map[65], const char path_boats_pos[]);


boolean_t treat_line(ship_t *ship, char * restrict * restrict splitted_line);


boolean_t check_boats_lengths(const char boats_lengths[4], const int len);


boolean_t check_too_many_chars(const int fd);

is_attack_valid_t get_attack(char **input);




boolean_t is_map_still_up(const char map[65]);

int game_actions(viewed_map_t gameboards, const boolean_t play_first);

void send_my_attack(const int nb);

char *get_input(void);

#endif /* MY_NAVY_H_ */