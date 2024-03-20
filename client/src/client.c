/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "client.h"

int receive_data(client_t *client, fd_set fds)
{
    if (FD_ISSET(client->socket, &fds)) {
        void *got = malloc(SIZE);
        ssize_t end = read(client->socket, got, SIZE);
        if (end <= 0)
            return 0;
        client->data = got;
        exe_response(client);
    }
    return 1;
}

int client_init(client_t *client, char **av)
{
    if ((client->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return (84);
    }
    client->serv_addr.sin_family = AF_INET;
    client->serv_addr.sin_port = htons(atoi(av[2]));
    if (inet_pton(AF_INET, av[1], &client->serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return (84);
    }
    int serv = connect(client->socket, (struct sockaddr *) &client->serv_addr,
        sizeof(client->serv_addr));
    if (serv < 0) {
        printf("\nConnection Failed \n");
        return (84);
    }
    return 0;
}

int client_loop(client_t *client, fd_set fds, int max_fd)
{
    while (client->state == PROCESS) {
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        FD_SET(client->socket, &fds);
        if (client->socket > max_fd) max_fd = client->socket;
        select(max_fd + 1, &fds, NULL, NULL, NULL);
        if (FD_ISSET(0, &fds)) {
            char got[2048];
            ssize_t size = read(0, &got, SIZE);
            got[size] = '\0';
            write_circular_buff(client->buff, got);
            memset(got, 0, SIZE);
        }
        exe_cmd(client, client->socket);
        if (!receive_data(client, fds)) return 0;
    }
    return 0;
}

int client_run(char **av)
{
    client_t *client = malloc(sizeof(client_t));
    fd_set fds = (fd_set) {0};
    int max_fd;
    client->socket = 0;
    client->state = PROCESS;
    client->data = NULL;
    client->uuid[0] = '\0';
    client->buff = new_circular_buff();

    if (client_init(client, av) == 84) return 0;
    max_fd = client->socket;
    return client_loop(client, fds, max_fd);
}
