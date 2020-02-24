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

//A boolean enum.
typedef enum boolean_e {
    FALSE,
    TRUE
} boolean_t;


//Enum used to check an attack validity.
typedef enum is_attack_valid_e {
    LEAVE,
    VALID,
    WRONG
} is_attack_valid_t;


//Enum used so that the program returns the correct value.
typedef enum game_winner_e {
    CURRENT_PLAYER = 0,
    ENEMY_PLAYER = 1,
    LEAVE_GAME = 0,
    ERROR = 84
} game_winner_t;


#endif /* NAVY_DEF_H_ */