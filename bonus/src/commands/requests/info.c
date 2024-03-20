/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "../../../include/command.h"

int info(client_t *client, char **args, int fd)
{
    s_info_request_t *request = malloc(sizeof(s_info_request_t));
    (void) args;

    request->code = INFO_REQUEST;
    strcpy(request->uuid, client->uuid);
    write(fd, request, sizeof(s_info_request_t));
    free(request);
    return 0;
}
