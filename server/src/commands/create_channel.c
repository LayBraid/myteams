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
    team_t const *team = NULL;
    user_list_t const *subs = NULL;
    client_t const *sub_client = NULL;

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
channel_t *channel, thread_t *thread)
{
    s_create_response_t *response = malloc(sizeof(s_create_response_t));

    if (!response) return -1;
    response->code = CREATE_RESPONSE;
    response->context = CONTEXT_CHANNEL;
    response->status_code = REQUEST_OK;
    strcpy(response->team_uuid, channel->team_uuid);
    strcpy(response->thread_uuid, thread->uuid);
    strcpy(response->uuid, client->uuid);
    response->timestamp = thread->timestamp;
    strcpy(response->name, thread->name);
    strcpy(response->body, thread->body);
    server_event_thread_created(channel->uuid, thread->uuid,
        client->uuid, thread->name, thread->body);
    notification(server, client, response);
    return 1;
}

int create_channel(server_t *server, client_t *client,
s_create_request_t *request, int restore)
{
    char *uuid = NULL;
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    if (request->first_arg[0] == '\0' ||
        request->second_arg[0] == '\0') return -1;
    if (find_team(server->database, client->context_team) == 0) return -1;
    team = get_team(server->database, client->context_team);
    strcpy(request->team_uuid, team->uuid);
    if (find_channel(team, client->context_channel) == 0) return -1;
    channel = get_channel(team, client->context_channel);
    strcpy(request->channel_uuid, channel->uuid);
    if (find_thread_by_name(channel, request->first_arg) != 0) return -1;
    uuid = add_thread(server->database, channel, request, restore);
    thread = get_thread(channel, uuid);
    if (restore) return 1;
    return response(server, client, channel, thread);
}
