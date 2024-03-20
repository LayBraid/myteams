/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

int create(client_t *client, char **args, int fd)
{
    s_create_request_t *request = malloc(sizeof(s_create_request_t));
    (void) client;

    request->code = CREATE_REQUEST;
    strcpy(request->uuid, client->uuid);
    strcpy(request->team_uuid, UUID_NONE);
    strcpy(request->channel_uuid, UUID_NONE);
    strcpy(request->thread_uuid, UUID_NONE);
    if (args[1] != NULL)
        strcpy(request->first_arg, args[1]);
    else
        request->first_arg[0] = '\0';
    if (args[2] != NULL)
        strcpy(request->second_arg, args[2]);
    else
        request->second_arg[0] = '\0';
    write(fd, request, sizeof(s_create_request_t));
    free(request);
    return 0;
}
