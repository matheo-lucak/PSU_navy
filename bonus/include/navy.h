/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Header to link the navy c files.
*/

#ifndef NAVY_H_

#define NAVY_H_

#include "navy_def.h"

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
typedef struct hostent HOSTENT;

//Structure used to stock both of the maps
typedef struct viewed_map_s {
    char ally_map[65];
    char enemy_map[65];
} viewed_map_t;

//Structure used to stock battleships characteristics.
typedef struct ship_s {
    int len;
    char begin[2];
    char end[2];
} ship_t;


/*
**                             ******************
**                             | Error Handlers |
**                             ******************
*/

//Prints the navy usage of the program onto the stdout.
//
//Returns TRUE if could write.
//Returns FALSE otherwise.
boolean_t usage(void);


/*
**                  ***********************************************
**                  | Different instances depending of the player |
**                  ***********************************************
*/

//Handles the game from the host side.
int navy_first_player(const char path_boats_pos[]);


//Handles the game from the guest side.
int navy_second_player(const char *hostname,
                            const char path_boats_pos[]);


/*
**                               ************************
**                               | Print-only functions |
**                               ************************
*/

//Prints:
//
//my pid: "pid"\n
void print_my_pid(void);


//Prints the ally and enemy gameboards.
boolean_t print_gameboards(viewed_map_t gameboards);


/*
**                                   *****************
**                                   | Maps Handling |
**                                   *****************
*/

//Memsets both ally and enemy strings with '.'.
//
//Calls get_given_boats() and Returns FALSE if this function returns FALSE.
boolean_t create_gameboards(viewed_map_t *gameboards,
                            const char path_boats_pos[]);

//Checks if a file contains the required boats.
boolean_t get_given_boats(char ally_map[65], const char path_boats_pos[]);

//Checks the given arguments in the given battleship config file.
boolean_t treat_boat_line(ship_t *ship, char **splitted_line);

//Checks if the given lengths are between 2 and 5 and they
//don't occur twice or more.
boolean_t check_boats_lengths(const char boats_lengths[4], const int len);

//Checks if some characters overflow the file.
boolean_t leftovers_in_file(const int fd);

/*
**                                     *************
**                                     | Game Loop |
**                                     *************
*/

//Main loop of the game, shifted for the two players.
int navy_game_actions(SOCKET sock, viewed_map_t gameboards,
                                    const boolean_t play_first);

//Checks if battleships are left onto a map.
boolean_t battleships_left(const char map[65]);


//Checks the validity of an input and free it in case of error
int check_attack_error(char *input);

//Gets an attack input while a valid one hasn't been given.
char *get_input(void);

//Sends an attack with a given spot to target.
boolean_t send_my_attack(SOCKET sock, const int nb);

//Places hit or missed onto your enemy_map if you hit the enemy or not.
boolean_t evaluate_my_attack(SOCKET sock, char enemy_map[65]);

//Places hit or missed onto your map if the enemy hit you or not.
boolean_t evaluate_enemy_attack(SOCKET sock, char ally_map[65]);

#endif /* NAVY_H_ */