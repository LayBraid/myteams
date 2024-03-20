/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "../../../include/command.h"

int use(client_t *client, char **args, int fd)
{
    s_use_request_t *request = malloc(sizeof(s_use_request_t));

    request->code = USE_REQUEST;
    if (client->uuid[0] != '\0') strcpy(request->uuid, client->uuid);
    if (args[1] != NULL)
        strcpy(request->team_uuid, args[1]);
    else
        request->team_uuid[0] = '\0';
    if (args[1] != NULL && args[2] != NULL)
        strcpy(request->channel_uuid, args[2]);
    else
        request->channel_uuid[0] = '\0';
    if (args[1] != NULL && args[2] != NULL && args[3] != NULL)
        strcpy(request->thread_uuid, args[3]);
    else
        request->thread_uuid[0] = '\0';
    write(fd, request, sizeof(s_use_request_t));
    free(request);
    return 0;
}
