/*
** EPITECH PROJECT, 2023
** server
** File description:
** ex00
*/

#include "command.h"

static int response(client_t *client, channel_t *channel)
{
    s_info_response_t *response = malloc(sizeof(s_info_response_t));

    response->code = INFO_RESPONSE;
    response->status_code = REQUEST_OK;
    response->context = CONTEXT_CHANNEL;
    response->error_code = NO_ERROR;
    response->user_status = client->logged;
    strcpy(response->channel_uuid, channel->uuid);
    strcpy(response->name, channel->name);
    strcpy(response->description, channel->description);
    write(client->socket.fd, response, sizeof(s_info_response_t));
    free(response);
    return 1;
}

static int not_found(client_t *client)
{
    s_info_response_t *response = malloc(sizeof(s_info_response_t));

    response->code = INFO_RESPONSE;
    response->status_code = REQUEST_KO;
    response->error_code = NOT_FOUND;
    response->context = CONTEXT_CHANNEL;
    write(client->socket.fd, response, sizeof(s_info_response_t));
    return 0;
}

int info_channel(server_t *server, client_t *client)
{
    team_t *team = get_team(server->database, client->context_team);
    channel_t *channel = get_channel(team, client->context_channel);

    if (channel == NULL) return not_found(client);
    return response(client, channel);
}
