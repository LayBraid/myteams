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
    return 0;
}

static int response(server_t *server, client_t *client,
thread_t *thread, message_t *message)
{
    s_create_response_t *response = malloc(sizeof(s_create_response_t));

    if (!response) return -1;
    response->code = CREATE_RESPONSE;
    response->context = CONTEXT_THREAD;
    response->status_code = REQUEST_OK;
    response->error_code = NO_ERROR;
    strcpy(response->team_uuid, thread->team_uuid);
    strcpy(response->thread_uuid, thread->uuid);
    strcpy(response->body, message->message);
    strcpy(response->uuid, client->uuid);
    response->timestamp = message->timestamp;
    strcpy(response->name, thread->name);
    server_event_reply_created(thread->uuid, client->uuid, message->message);
    notification(server, client, response);
    free(response);
    return 1;
}

int create_thread(server_t *server, client_t *client,
s_create_request_t *request, int restore)
{
    char *uuid = NULL;
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;
    message_t *message = NULL;

    if (request->first_arg[0] == '\0' ||
        request->second_arg[0] == '\0') return -1;
    if (find_team(server->database, client->context_team) == 0) return -1;
    team = get_team(server->database, client->context_team);
    strcpy(request->team_uuid, team->uuid);
    if (find_channel(team, client->context_channel) == 0) return -1;
    channel = get_channel(team, client->context_channel);
    strcpy(request->channel_uuid, channel->uuid);
    thread = get_thread(channel, client->context_thread);
    strcpy(request->thread_uuid, thread->uuid);
    uuid = add_message_to_thread(server->database, request, thread, restore);
    message = get_message_in_thread(thread, uuid);
    if (restore) return 1;
    return response(server, client, thread, message);
}
