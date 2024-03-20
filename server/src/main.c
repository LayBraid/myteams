/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "main.h"

int main(int ac, char **av)
{
    int ret;
    server_t *serv;
    int connection_porte;

    srand(time(NULL));
    signal(SIGINT, SIGNAL_CAST sigint_handler);
    if (ac < 2) {
        printf("Usage: ./myftp port\n");
        return 84;
    }
    connection_porte = atoi(av[1]);
    serv = new_server(connection_porte);
    database_init(serv);
    ret = run_serv(serv);
    delete_server(serv);
    return ret;
}
