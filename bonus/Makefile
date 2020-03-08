##
## EPITECH PROJECT, 2019
## Makefile navy
## File description:
## compiles c files with libs into the navy program
##

SRC			=	src/usage.c										\
				src/print_my_pid.c								\
				src/attacks_handling/evaluate_attacks.c			\
				src/attacks_handling/get_and_send_attacks.c		\
				src/gameboards_handling/create_gameboards.c		\
				src/attacks_handling/get_input.c				\
				src/gameboards_handling/get_given_boats.c		\
				src/gameboards_handling/endgame_condition.c		\
				src/gameboards_handling/navy_game_actions.c		\
				src/gameboards_handling/print_gameboards.c		\
				src/gameboards_handling/ships_error_handling.c	\
				src/gameboards_handling/update_map.c			\
				src/players_sides/navy_first_player.c			\
				src/players_sides/navy_second_player.c			\

MAIN		=	src/main.c

VPATH		=	/usr/local/lib/

NAME		=	navy

CFLAGS		=	-Wall -Wextra

CPPFLAGS	=	-I./include/

LDFLAGS		=	-L../lib/

LDLIBS		=	-lmy

LDLIBTEST	=	-lmy -lcriterion

all:	$(NAME)

$(NAME):
	$(MAKE) -sC ../lib/my
	$(CC) -o $@ $(MAIN) $(SRC) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

debug:
	$(MAKE) -sC ../lib/my
	$(CC) -g -o $@ $(SRC) $(MAIN) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(NAME)
	$(RM) debug
	$(RM) tests_run
	$(RM) *.gcda *.gcno
	$(RM) vgcore.*

fclean:	clean
	$(MAKE) fclean -sC ../lib/my

re:	fclean all

.NOTPARALLEL:
.PHONY: all debug tests_run coverage clean fclean re