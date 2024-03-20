/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

static int next_handle(s_info_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_CHANNEL) {
        client_print_channel(response->channel_uuid,
            response->name, response->description);
        return 1;
    }
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_THREAD) {
        client_print_thread(response->thread_uuid,
            response->uuid, response->timestamp, response->name,
            response->body);
        return 1;
    }
    return 0;
}

static int handle(s_info_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_NONE) {
        client_print_user(response->uuid,
            response->name, response->user_status);
        return 1;
    }
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_TEAM) {
        client_print_team(response->team_uuid,
            response->name, response->description);
        return 1;
    }
    return next_handle(response);
}

int info_response(client_t *client, void *payload)
{
    (void) client;
    s_info_response_t *response = UNMARSHALL(info_response) payload;

    if (response->status_code == REQUEST_KO &&
        response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 1;
    }
    return handle(response);
}
