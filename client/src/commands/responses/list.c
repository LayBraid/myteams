/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

static int next_handle(s_list_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_CHANNEL) {
        client_channel_print_threads(response->thread_uuid,
            response->uuid, response->timestamp,
            response->name, response->body);
        return 1;
    }
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_THREAD) {
        client_thread_print_replies(response->thread_uuid,
            response->uuid, response->timestamp, response->body);
        return 1;
    }
    return 0;
}

static int handle(s_list_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_NONE) {
        client_print_teams(response->team_uuid,
            response->name, response->description);
        return 1;
    }
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_TEAM) {
        client_team_print_channels(response->channel_uuid,
            response->name, response->description);
        return 1;
    }
    return next_handle(response);
}

int list_response(client_t *client, void *payload)
{
    (void) client;
    s_list_response_t *response = UNMARSHALL(list_response) payload;

    if (response->status_code == REQUEST_KO &&
        response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 1;
    }
    return handle(response);
}
