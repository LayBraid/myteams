/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "server.h"

server_t *new_server(int connection_port)
{
    server_t *server = malloc(sizeof(server_t));
    if (server == NULL)
        return (NULL);

    server->control_socket = new_control_socket(connection_port);
    server->client_list = NULL;

    return server;
}

void *delete_server(server_t *server)
{
    if (server == NULL)
        return NULL;
    close(server->control_socket->fd);
    free(server->control_socket);
    while (server->client_list) {
        delete_client(server, server->client_list, &server->client_list, 1);
    }
    free(server);
    return NULL;
}

static void handle_conn(server_t *serv)
{
    client_t *client = get_client(&serv->client_list,
        serv->control_socket->fd);
    if (client)
        return;
    client = new_client(serv->control_socket->fd);
    push(&serv->client_list, client);
}

int run_serv(server_t *serv)
{
    int max_fd = serv->control_socket->fd;

    serv->readfds = (fd_set) {0};
    while (!sigint(false)) {
        FD_ZERO(&serv->readfds);
        FD_SET(serv->control_socket->fd, &serv->readfds);
        FOR_EACH(serv, &serv->client_list, set_fd, &serv->readfds, &max_fd);
        int activity = select(max_fd + 1, &serv->readfds, NULL, NULL, NULL);
        if (activity == -1)
            return 84;
        if (FD_ISSET(serv->control_socket->fd, &serv->readfds))
            handle_conn(serv);
        FOR_EACH(serv, &serv->client_list, check_read_fd, &serv->readfds)
        FOR_EACH_SRV(&serv->client_list, serv, handle_commands)
        FOR_EACH(serv, &serv->client_list, check_disconnect)
    }
    return 0;
}
