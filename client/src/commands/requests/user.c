/*
** EPITECH PROJECT, 2023
** client
** File description:
** user
*/

#include "command.h"

int user(client_t *client, char **args, int fd)
{
    if (args[1] == NULL)
        return -1;

    (void) client;
    s_user_request_t *request = malloc(sizeof(s_user_request_t));

    request->code = USER_REQUEST;
    strcpy(request->uuid, args[1]);

    write(fd, request, sizeof(s_user_request_t));
    free(request);
    return 0;
}