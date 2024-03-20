##
## EPITECH PROJECT, 2021
## makefile
## File description:
## Makefile
##

CC	=	gcc

SRC	=	$(wildcard src/*.c) \
		$(wildcard src/**/*.c) \
		$(wildcard src/**/**/*.c)

INCLUDE	=	-Iinclude

OBJ	=	$(SRC:.c=.o)

CFLAGS	= 	-Wall -Wextra -g3

CFLAGS 	+= $(INCLUDE)

NAME	=	teams_tester

all:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
		rm -f $(OBJ)
		rm -f unit-test*
		rm -f vgcore.*

fclean: clean
		rm -f $(NAME)

re:	fclean all
