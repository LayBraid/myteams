/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

int help(client_t *client, char **args, int fd)
{
    s_help_request_t *request = malloc(sizeof(s_help_request_t));
    (void) args;
    (void) client;

    request->code = HELP_REQUEST;
    write(fd, request, sizeof(s_help_request_t));
    free(request);
    return 0;
}
