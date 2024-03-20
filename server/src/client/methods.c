/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "client.h"

int set_fd(client_t *client, fd_set *readfds, int *max_fd)
{
    FD_SET(client->socket.fd, readfds);
    if (client->socket.fd > *max_fd)
        *max_fd = client->socket.fd;
    return 0;
}

int check_read_fd(client_t *client, fd_set *readfds)
{
    if (FD_ISSET(client->socket.fd, readfds)) {
        void *wait = malloc(2048);
        ssize_t end = read(client->socket.fd, wait, 2048);
        if (end <= 0)
            return 1;
        client->rec = wait;
    }
    return 0;
}

int check_disconnect(client_t *client)
{
    if (client->status == DISCONNECTED)
        return 1;
    return 0;
}
