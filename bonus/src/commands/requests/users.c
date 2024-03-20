/*
** EPITECH PROJECT, 2023
** client
** File description:
** users
*/

#include "../../../include/command.h"

int users(client_t *client, char **args, int fd)
{
    (void) client;
    s_users_request_t *request = malloc(sizeof(s_users_request_t));

    request->code = USERS_REQUEST;
    write(fd, request, sizeof(s_users_request_t));
    free(request);
    return 0;
}
