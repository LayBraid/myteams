/*
** EPITECH PROJECT, 2023
** client
** File description:
** subscribed
*/

#include "command.h"

int subscribed(client_t *client, char **args, int fd)
{
    (void) client;
    s_subscribed_request_t *request = malloc(sizeof(s_subscribed_request_t));

    strcpy(request->uuid, client->uuid);
    strcpy(request->team_uuid, "");
    request->code = SUBSCRIBED_REQUEST;

    if (args[1] != NULL)
        strcpy(request->team_uuid, args[1]);

    write(fd, request, sizeof(s_subscribed_request_t));
    free(request);
    return 0;
}
