/*
** EPITECH PROJECT, 2023
** client
** File description:
** subscribe
*/

#include "command.h"

int subscribe(client_t *client, char **args, int fd)
{
    if (args[1] == NULL)
        return -1;

    (void) client;
    s_subscribe_request_t *request = malloc(sizeof(s_subscribe_request_t));

    request->code = SUBSCRIBE_REQUEST;
    strcpy(request->uuid_user, client->uuid);
    strcpy(request->uuid_team, args[1]);

    write(fd, request, sizeof(s_subscribe_request_t));
    free(request);
    return 0;
}
