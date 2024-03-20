/*
** EPITECH PROJECT, 2023
** client
** File description:
** subscribe
*/

#include "command.h"

int subscribe_response(client_t *client, void *payload)
{
    (void) client;
    s_subscribe_response_t *response = UNMARSHALL(subscribe_response) payload;

    if (response->status_code == REQEST_UNAUTHORIZED
        && response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 0;
    }

    if (response->status_code == REQUEST_OK
    && response->error_code != ALREADY_CONNECTED)
        client_print_subscribed(response->uuid_user, response->uuid_team);
    else
        return -1;
    return 0;
}
