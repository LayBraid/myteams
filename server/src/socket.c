/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "socket.h"

socket_t *new_control_socket(int connection_port)
{
    socket_t *control_sock = malloc(sizeof(socket_t));
    if (control_sock == NULL)
        return (NULL);
    control_sock->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (control_sock->fd == -1) return 0;
    control_sock->saddr.sin_family = AF_INET;
    control_sock->saddr.sin_port = htons(connection_port);
    control_sock->saddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(control_sock->fd, (const struct sockaddr *)&control_sock->saddr,
            sizeof(struct sockaddr_in)) == -1) {
        exit(84);
    }
    if (listen(control_sock->fd, 20) == -1) {
        return NULL;
    }
    return control_sock;
}

data_socket_t *connect_data_socket(data_socket_t *data_sock, int port, char *ip)
{
    data_sock->sock.saddr.sin_port = htons(port);
    data_sock->sock.saddr.sin_addr.s_addr = inet_addr(ip);
    if (connect(data_sock->sock.fd,
    (const struct sockaddr *)&(data_sock->sock.saddr),
    sizeof(struct sockaddr_in)) == -1) {
        return NULL;
    }
    return data_sock;
}

void delete_data_socket(data_socket_t *data_sock)
{
    close(data_sock->sock.fd);
    free(data_sock);
}
