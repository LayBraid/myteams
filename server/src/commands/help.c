/*
** EPITECH PROJECT, 2023
** teams
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int help(server_t *server, client_t *client, void *payload, int restore)
{
    (void) server;
    (void) restore;
    s_help_request_t *s = UNMARSHALL(help_request) payload;
    s_help_response_t *response = malloc(sizeof(s_help_response_t));
    (void) s;

    response->code = HELP_RESPONSE;
    response->status_code = REQUEST_OK;
    response->error_code = NO_ERROR;
    write(client->socket.fd, response, sizeof(s_help_response_t));
    return 0;
}
