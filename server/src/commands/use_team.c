/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static s_use_request_t *format_request(s_use_request_t *request)
{
    if (strlen(request->team_uuid) == 0)
        strcpy(request->team_uuid, UUID_NONE);
    if (strlen(request->channel_uuid) == 0)
        strcpy(request->channel_uuid, UUID_NONE);
    if (strlen(request->thread_uuid) == 0)
        strcpy(request->thread_uuid, UUID_NONE);
    return request;
}

static int response(client_t *client)
{
    s_use_response_t *response = malloc(sizeof(s_use_response_t));

    strcpy(response->uuid, client->uuid);
    strcpy(response->team_uuid, client->context_team);
    strcpy(response->channel_uuid, UUID_NONE);
    strcpy(response->thread_uuid, UUID_NONE);
    response->code = USE_RESPONSE;
    response->error_code = NO_ERROR;
    response->status_code = REQUEST_OK;
    response->context = CONTEXT_TEAM;
    write(client->socket.fd, response, sizeof(s_use_response_t));
    free(response);
    return 1;
}

int use_team(server_t *server, client_t *client,
s_use_request_t *request, int restore)
{
    team_t *team = NULL;

    if (!find_team(server->database, request->team_uuid)) return 0;
    team = get_team(server->database, request->team_uuid);
    strcpy(client->context_team, team->uuid);
    strcpy(client->context_channel, UUID_NONE);
    strcpy(client->context_thread, UUID_NONE);
    if (!restore) write_context(server->database, format_request(request));
    if (restore) return 1;
    return response(client);
}