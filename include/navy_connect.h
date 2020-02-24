/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Connection and communication header side of the navy program.
*/

#ifndef NAVY_CONNECT_H_

#define NAVY_CONNECT_H_

#include <signal.h>
#include "navy_def.h"

//Structure used to stock a 6-bit unsigned integer use for
//players communication.
//
//The 6 consecutive signals will either be SIGUSR1 or SIGUSR2 and
//will be stocked into an int to process binary-targeted space onto
//the battlefield.
//
//
//For instance:
//If a player wants to target G3, the G3 space corresponds to the
//19th space onto the battlefield so the user will send 19 in binary:
//
//010011 -> SIGUSR1 correspond to 0 and SIGUSR2 to 1.
//(2^5 * 0) + (2^4 * 1) + (2^3 * 0) + (2^2 * 0) + (2^1 * 1) + (2^0 * 1).
//
//6 bits are set to limit the unsigned int to a 0-63 range as the 8 by 8
//map is 64 spaces at total.
typedef struct binary_signal_s {
    unsigned int bridge : 6;
} binary_signal_t;


//Structure used to stock:
//
//
//sa -> sigaction :
//Sigaction struct containing information
//on how to treat a received signal data.
//
//is_connected :
//A boolean used to know if our program has catched a
//signal from the other player.
//
//catched_signal :
//Corresponds to either SIGUSR1 or SIGUSR2 if either one
//has been caught or to UNDEFINED if none of those two
//have been caught.
//
//enemy_pid :
//The enemy pid.
typedef struct connection_info_s {
    struct sigaction sa;
    boolean_t is_connected;
    int catched_signal;
    int enemy_pid;
} connection_info_t;


//Used global structure to access connection informations inside of
//the sa_handler function.
connection_info_t co_info;



/*
**                          ******************************
**                          | Signals Handlers Functions |
**                          ******************************
*/

//Whenever a SIGUSR2 signal is caught, sets the co_info.enemy_pid to
//the sender's pid.
void get_enemy_pid(const int sig_num, siginfo_t *info, void *vp);

//Whenever a SIGUSR1 or SIGUSR2 is caught and the sender's pid matches with
//co_info.enemy_pid, sets co_info.enemy_pid to TRUE and catched_signal to
//the caught signal.
void get_enemy_signal(const int sig_num, siginfo_t *info, void *vp);

//Resets to sighandlers functions to a new position in the code and resets
//the co_info.is_connected to FALSE and catched_signal to UNDEFINED.
void refresh_siginterpret(void);



/*
**                    ********************************************
**                    | Game Loop Side that need binary_signal_t |
**                    ********************************************
*/

//Waits for 6 SIGUSR1 and/or SIGUSR2 signals and sets a 6-bit unsigned int,
//with the protocol method, and returns int inside of a binary_signal_t
//structure.
binary_signal_t get_enemy_attack(void);;

//Given a map to change an a 6-bit unsigned int, modifies the space taken
//by this spot to either a hit 'x' or a miss 'o'.
boolean_t update_map(char map[65], const binary_signal_t target);

#endif /* NAVY_CONNECT_H_ */