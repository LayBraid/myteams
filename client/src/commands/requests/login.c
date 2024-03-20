/*
** EPITECH PROJECT, 2023
** playground
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int login(client_t *client, char **args, int fd)
{
    (void) client;
    s_login_request_t *request = malloc(sizeof(s_login_request_t));

    request->code = LOGIN_REQUEST;
    strcpy(request->username, args[1]);
    write(fd, request, sizeof(s_login_request_t));
    free(request);
    return 0;
}