##
## EPITECH PROJECT, 2021
## makefile
## File description:
## Makefile
##

all:
		make -C client/
		make -C server/

clean:
		make -C client/ clean
		make -C server/ clean

tests_run:
		make -C client/ tests_run
		make -C server/ tests_run

cov:
		make -C client/ cov
		make -C server/ cov

fclean:
		make -C client/ fclean
		make -C server/ fclean

re:
		make -C client/ re
		make -C server/ re
