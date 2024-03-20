/*
** EPITECH PROJECT, 2023
** server
** File description:
** ex00
*/

#include "command.h"

static int response(client_t *client, thread_t *thread, message_t *message)
{
    s_list_response_t *response = malloc(sizeof(s_list_response_t));

    response->code = LIST_RESPONSE;
    response->status_code = REQUEST_OK;
    response->context = CONTEXT_THREAD;
    response->error_code = NO_ERROR;
    strcpy(response->thread_uuid, thread->uuid);
    strcpy(response->uuid, message->sender_uuid);
    strcpy(response->body, message->message);
    response->timestamp = message->timestamp;
    write(client->socket.fd, response, sizeof(s_list_response_t));
    free(response);
    return 1;
}

int list_thread(server_t *server, client_t *client)
{
    team_t *team = get_team(server->database, client->context_team);
    channel_t *channel = get_channel(team, client->context_channel);
    thread_t *thread = get_thread(channel, client->context_thread);
    message_t *message = thread->messages;

    if (message == NULL) return 0;
    while (message != NULL) {
        response(client, thread, message);
        message = message->next;
        usleep(20);
    }
    return 1;
}
