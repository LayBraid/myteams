/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#ifndef CLIENT_CLIENT_H
    #define CLIENT_CLIENT_H

    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include "../../shared/include/proto.h"
    #include "circular_buff.h"

enum {
    PROCESS,
    QUIT,
};

typedef struct client_s {
    int state;
    int socket;
    char uuid[37];
    char username[32];
    void *data;
    struct sockaddr_in serv_addr;
    circular_buff_t *buff;
    use_context context;
} client_t;

int client_run(char **av);

void exe_cmd(client_t *client, int fd);

int exe_response(client_t *client);

void free_tab(char **tab);

circular_buff_t *new_circular_buff(void);

bool write_circular_buff(circular_buff_t *buff, char *str);

#endif //CLIENT_CLIENT_H
