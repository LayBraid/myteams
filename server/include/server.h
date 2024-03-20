/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "client.h"
    #include "command.h"
    #include "database.h"
    #include "struct.h"

typedef struct server_s server_t;

socket_t *new_control_socket(int connection_port);
client_t *new_client(int fd);
int delete_client(server_t *server, client_t *to_delete,
    client_t **list, bool force);
client_t *get_client(client_t **list, int fd);
void push(client_t **list, client_t *new_sock);

/* ### CLIENT METHODS ### */
int set_fd(client_t *client, fd_set *readfds, int *max_fd);
int check_read_fd(client_t *client, fd_set *readfds);
int handle_commands(server_t *server, client_t *client);
int write_needed(client_t *client);
int check_disconnect(client_t *client);


bool sigint(bool set);

    #define REP_220 "220 Service ready for new user.\r\n"

#endif //SERVER_H_
