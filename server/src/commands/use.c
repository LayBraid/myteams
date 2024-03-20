/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int response_not_connected(client_t *client)
{
    s_use_response_t *response = malloc(sizeof(s_use_response_t));

    strcpy(response->uuid, client->uuid);
    strcpy(response->team_uuid, UUID_NONE);
    strcpy(response->channel_uuid, UUID_NONE);
    strcpy(response->thread_uuid, UUID_NONE);
    response->code = USE_RESPONSE;
    response->status_code = REQUEST_KO;
    response->error_code = NOT_CONNECTED;
    response->context = CONTEXT_NONE;
    write(client->socket.fd, response, sizeof(s_use_response_t));
    free(response);
    return 1;
}

int use(server_t *server, client_t *client, void *payload, int restore)
{
    s_use_request_t *request = UNMARSHALL(use_request) payload;
    int context = get_context(request);

    if (!restore && !client->logged) return response_not_connected(client);
    if (context == CONTEXT_NONE)
        return use_none(server, client, request, restore);
    if (context == CONTEXT_TEAM)
        return use_team(server, client, request, restore);
    if (context == CONTEXT_CHANNEL)
        return use_channel(server, client, request, restore);
    if (context == CONTEXT_THREAD)
        return use_thread(server, client, request, restore);
    return 0;
}
