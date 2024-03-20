/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

static int next_handle(client_t *client, s_use_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_THREAD) {
        client->context = CONTEXT_THREAD;
    }
    return 0;
}

static int response_handle(client_t *client, s_use_response_t *response)
{
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_NONE) {
        client->context = CONTEXT_NONE;
    }
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_TEAM) {
        client->context = CONTEXT_TEAM;
    }
    if (response->status_code == REQUEST_OK &&
        response->context == CONTEXT_CHANNEL) {
        client->context = CONTEXT_CHANNEL;
    }
    return next_handle(client, response);
}

int use_response(client_t *client, void *payload)
{
    (void) client;
    s_use_response_t *response = UNMARSHALL(use_response) payload;

    if (response->status_code == REQUEST_KO &&
        response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 1;
    }
    return response_handle(client, response);
}
