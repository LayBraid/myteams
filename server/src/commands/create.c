/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int response_not_connected(client_t *client)
{
    s_create_response_t *response = malloc(sizeof(s_create_response_t));

    response->code = CREATE_RESPONSE;
    response->status_code = REQUEST_KO;
    response->error_code = NOT_CONNECTED;
    write(client->socket.fd, response, sizeof(s_create_response_t));
    free(response);
    return 1;
}

int create(server_t *server, client_t *client, void *payload, int restore)
{
    s_create_request_t *request = UNMARSHALL(create_request) payload;
    int context = local_context(client);

    if (!restore && !client->logged) return response_not_connected(client);
    if (context == CONTEXT_NONE) return create_none(server, client,
        request, restore);
    if (context == CONTEXT_TEAM) return create_team(server, client,
        request, restore);
    if (context == CONTEXT_CHANNEL) return create_channel(server, client,
        request, restore);
    if (context == CONTEXT_THREAD) return create_thread(server, client,
        request, restore);
    return 0;
}
