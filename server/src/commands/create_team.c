/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int notification(server_t *server, client_t *client,
s_create_response_t *response)
{
    team_t *team = NULL;
    user_list_t *subs = NULL;
    client_t *sub_client = NULL;

    NOTIFY_CREATE(client);
    team = get_team(server->database, response->team_uuid);
    if (!team) return -1;
    subs = team->users_subscribed;
    if (!subs) return -1;
    while (subs) {
        sub_client = find_client(server, subs->user->uuid);
        if (strcmp(sub_client->uuid, client->uuid) == 0) {
            subs = subs->next;
            continue;
        }
        NOTIFY_CREATE(sub_client);
        subs = subs->next;
    }
    free(response);
    return 0;
}

static int response(server_t *server, client_t *client,
team_t *team, channel_t *channel)
{
    s_create_response_t *response = malloc(sizeof(s_create_response_t));

    if (!response) return -1;
    response->code = CREATE_RESPONSE;
    response->context = CONTEXT_TEAM;
    response->status_code = REQUEST_OK;
    response->error_code = NO_ERROR;
    strcpy(response->team_uuid, team->uuid);
    strcpy(response->channel_uuid, channel->uuid);
    strcpy(response->name, channel->name);
    strcpy(response->description, channel->description);
    server_event_channel_created(team->uuid, channel->uuid, channel->name);
    notification(server, client, response);
    return 1;
}

int create_team(server_t *server, client_t *client,
s_create_request_t *request, int restore)
{
    char *uuid = NULL;
    team_t *team = NULL;
    channel_t *channel = NULL;

    if (request->first_arg[0] == '\0' ||
        request->second_arg[0] == '\0') return -1;
    if (find_team(server->database, client->context_team) == 0) return -1;
    team = get_team(server->database, client->context_team);
    strcpy(request->team_uuid, team->uuid);
    uuid = add_channel(server->database, request, restore, team->uuid);
    channel = get_channel(team, uuid);
    if (restore) return 1;
    return response(server, client, team, channel);
}
