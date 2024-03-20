/*
** EPITECH PROJECT, 2023
** server
** File description:
** ex00
*/

#include "command.h"

static int response(client_t *client, thread_t *thread)
{
    s_info_response_t *response = malloc(sizeof(s_info_response_t));

    response->code = INFO_RESPONSE;
    response->status_code = REQUEST_OK;
    response->context = CONTEXT_THREAD;
    response->error_code = NO_ERROR;
    response->user_status = client->logged;
    strcpy(response->thread_uuid, thread->uuid);
    strcpy(response->uuid, thread->uuid_creator);
    strcpy(response->name, thread->name);
    strcpy(response->body, thread->body);
    response->timestamp = thread->timestamp;
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
    response->context = CONTEXT_THREAD;
    write(client->socket.fd, response, sizeof(s_info_response_t));
    return 0;
}

int info_thread(server_t *server, client_t *client)
{
    team_t *team = get_team(server->database, client->context_team);
    channel_t *channel = get_channel(team, client->context_channel);
    thread_t *thread = get_thread(channel, client->context_thread);

    if (thread == NULL) return not_found(client);
    return response(client, thread);
}
