/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

static int last_handle(s_create_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_THREAD) {
        client_event_thread_reply_received(response->team_uuid,
            response->thread_uuid,response->uuid,response->body);
        client_print_reply_created(response->thread_uuid, response->uuid,
            response->timestamp, response->body);
    }
    return 0;
}

static int new_handle(s_create_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_CHANNEL) {
        client_event_thread_created(response->thread_uuid, response->uuid,
            response->timestamp, response->name, response->body);
        client_print_thread_created(response->thread_uuid, response->uuid,
            response->timestamp, response->name, response->body);
    }
    return last_handle(response);
}

static int response_handle(s_create_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_NONE) {
        client_event_team_created(response->team_uuid,
            response->name, response->description);
        client_print_team_created(response->team_uuid,
            response->name, response->description);
    }
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_TEAM) {
        client_event_channel_created(response->channel_uuid,
            response->name, response->description);
        client_print_channel_created(response->channel_uuid,
            response->name, response->description);
    }
    return new_handle(response);
}

int create_response(client_t *client, void *payload)
{
    (void) client;
    s_create_response_t *response = UNMARSHALL(create_response) payload;

    if (response->status_code == REQUEST_KO &&
        response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 1;
    }
    if (response->status_code == REQUEST_KO &&
        response->error_code == ALREADY_EXIST) {
        return 1;
    }
    return response_handle(response);
}
