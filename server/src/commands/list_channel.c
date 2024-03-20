/*
** EPITECH PROJECT, 2023
** server
** File description:
** ex00
*/

#include "command.h"

static int response(client_t *client, thread_t *thread)
{
    s_list_response_t *response = malloc(sizeof(s_list_response_t));

    response->code = LIST_RESPONSE;
    response->status_code = REQUEST_OK;
    response->context = CONTEXT_CHANNEL;
    response->error_code = NO_ERROR;
    strcpy(response->channel_uuid, thread->uuid);
    strcpy(response->uuid, thread->uuid_creator);
    strcpy(response->name, thread->name);
    strcpy(response->description, thread->description);
    strcpy(response->body, thread->body);
    response->timestamp = thread->timestamp;
    write(client->socket.fd, response, sizeof(s_list_response_t));
    free(response);
    return 1;
}

int list_channel(server_t *server, client_t *client)
{
    team_t *team = get_team(server->database, client->context_team);
    channel_t *channel = get_channel(team, client->context_channel);
    thread_t *thread = channel->threads;

    if (thread == NULL) return 0;
    while (thread != NULL) {
        response(client, thread);
        thread = thread->next;
        usleep(20);
    }
    return 1;
}
