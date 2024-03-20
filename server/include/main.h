/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/
#ifndef MAIN_H_
    #define MAIN_H_

    #include <stdlib.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <signal.h>
    #include "server.h"
    #include "inc.h"
    #include "database.h"

    #ifdef __APPLE__
        #define SIGNAL_CAST (sig_t)
    #else
        #define SIGNAL_CAST (__sighandler_t)
    #endif

server_t *new_server(int connection_port);
void *delete_server(server_t *server);
int run_serv(server_t *serv);

void sigint_handler(void);

#endif //MAIN_H_
