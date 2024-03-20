##
## EPITECH PROJECT, 2021
## makefile
## File description:
## Makefile
##

CC	=	gcc

SRC	=	$(wildcard src/*.c) \
		$(wildcard src/**/*.c) \
		$(wildcard ../shared/*.c) \
		$(wildcard ../shared/**/*.c)

TESTED_SRC	=	$(filter-out src/main.c \
				$(wildcard src/*.c)) \
				$(wildcard src/**/*.c) \
				$(wildcard ../shared/*.c) \

TESTS_SRC	=	$(wildcard tests/*.c) \
			$(wildcard tests/**/*.c) \
			$(wildcard ../shared/*.c) \
			$(wildcard ../shared/**/*.c) \
			$(wildcard ../libs/myteams/*.c) \

INCLUDE	=	-Iinclude -I../libs/myteams -I../shared/include
LIB	=	-L ../libs/myteams -l myteams

OBJ	=	$(SRC:.c=.o)

CFLAGS	= 	-Wall -Wextra -g3
TFLAGS 	= -lcriterion -o ./unit-tests --coverage

CFLAGS 	+= $(INCLUDE)
TFLAGS	+= $(INCLUDE)

NAME	= myteams_server

all:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIB)
		mv $(NAME) ../

clean:
		rm -f $(OBJ)
		rm -f unit-test*
		rm -f vgcore.*
		rm -f *.gc**

tests_run:
			gcc $(TESTED_SRC) $(TESTS_SRC) $(TFLAGS) $(INCLUDE) $(LIB)
			./unit-tests

cov:
			$(CC) $(TESTED_SRC) $(TESTS_SRC) $(LIB) $(TFLAGS)
			./unit-tests
			gcovr .

fclean: clean
		rm -f ../$(NAME)

re:	fclean all
