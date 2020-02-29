/*
** EPITECH PROJECT, 2019
** PSU_navy_2019
** File description:
** Enums and macros adapted to the navy project.
*/

#ifndef NAVY_DEF_H_

#define NAVY_DEF_H_

//Macro defined to express that none
//of the SIGUSR1 or SIGUSR2 have been caught.
#define UNDEFINED -1

//Returns a one-dimentional navy map coordinate from a two-dimentionnal one.
#define get_target_aim(x, y) 8 * (y - '1') + x - 'A'

//A boolean enum.
typedef enum boolean_e {
    FALSE,
    TRUE
} boolean_t;

typedef enum game_intervals_e {
    LEAVE,
    CONTINUE,
    MID_CURRENT_PLAYER,
    MID_ENEMY_PLAYER
} game_intervals_t;


//Enum used to check an attack validity.
typedef enum is_attack_valid_e {
    VALID = 1,
    WRONG = 2
} is_attack_valid_t;


//Enum used so that the program returns the correct value.
typedef enum game_winner_e {
    CURRENT_PLAYER = 0,
    ENEMY_PLAYER = 1,
    ERROR = 84
} game_winner_t;


#endif /* NAVY_DEF_H_ */