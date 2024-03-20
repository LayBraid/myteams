/*
** EPITECH PROJECT, 2023
** server
** File description:
** ex00
*/

#include "command.h"

static int response_not_connected(client_t *client)
{
    s_list_response_t *response = malloc(sizeof(s_list_response_t));

    response->code = LIST_RESPONSE;
    response->status_code = REQUEST_KO;
    response->error_code = NOT_CONNECTED;
    write(client->socket.fd, response, sizeof(s_list_response_t));
    free(response);
    return 1;
}

int list(server_t *server, client_t *client, void *payload, int restore)
{
    s_list_request_t *request = UNMARSHALL(list_request) payload;
    int context = local_context(client);
    (void) request;

    if (!restore && !client->logged) return response_not_connected(client);
    if (context == CONTEXT_NONE)
        return list_none(server, client);
    if (context == CONTEXT_TEAM)
        return list_team(server, client);
    if (context == CONTEXT_CHANNEL)
        return list_channel(server, client);
    if (context == CONTEXT_THREAD)
        return list_thread(server, client);
    return 0;
}
