/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

int logout(client_t *client, char **args, int fd)
{
    (void) args;
    s_logout_request_t *request = malloc(sizeof(s_logout_request_t));

    request->code = LOGOUT_REQUEST;
    if (client->uuid[0] != '\0')
        strcpy(request->uuid, client->uuid);
    write(fd, request, sizeof(s_logout_request_t));
    free(request);
    return 0;
}
