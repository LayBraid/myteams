/*
** EPITECH PROJECT, 2023
** server
** File description:
** ex00
*/

#include "command.h"

static int response(client_t *client, channel_t *channel)
{
    s_list_response_t *response = malloc(sizeof(s_list_response_t));

    response->code = LIST_RESPONSE;
    response->status_code = REQUEST_OK;
    response->context = CONTEXT_TEAM;
    response->error_code = NO_ERROR;
    strcpy(response->channel_uuid, channel->uuid);
    strcpy(response->uuid, channel->uuid_creator);
    strcpy(response->name, channel->name);
    strcpy(response->description, channel->description);
    write(client->socket.fd, response, sizeof(s_list_response_t));
    free(response);
    return 1;
}

int list_team(server_t *server, client_t *client)
{
    team_t *team = get_team(server->database, client->context_team);
    channel_t *channel = team->channels;

    if (channel == NULL) return 0;
    while (channel != NULL) {
        response(client, channel);
        channel = channel->next;
        usleep(20);
    }
    return 1;
}
