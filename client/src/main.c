/*
** EPITECH PROJECT, 2023
** playground
** File description:
** No file there , just an epitech header example
*/

#include "client.h"

int main(int ac, char **av)
{
    if (ac != 3) {
        printf("USAGE: ./client ip port\n");
        return (84);
    }
    return client_run(av);
}
