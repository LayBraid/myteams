/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#ifndef SOCKET_H_
    #define SOCKET_H_

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <string.h>
    #include "inc.h"
    #include "proto_buff.h"

typedef struct socket_s {
    int fd;
    struct sockaddr_in saddr;
} socket_t;

typedef struct data_socket_s {
    int parent_fd;
    int connected_fd;
    circular_buff_t *read_buff;
    socket_t sock;
} data_socket_t;

circular_buff_t *new_circular_buff(void);
char *get_next_cmd(circular_buff_t *buff);

#endif //SOCKET_H_
