/*
** EPITECH PROJECT, 2023
** client
** File description:
** unsubscribe
*/

#include "command.h"

int unsubscribe_response(client_t *client, void *payload)
{
    (void) client;
    s_unsub_response_t *response = UNMARSHALL(unsub_response) payload;

    if (response->status_code == REQEST_UNAUTHORIZED
        && response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 0;
    }

    if (response->status_code == REQUEST_OK
        && response->error_code != NOT_CONNECTED)
        client_print_unsubscribed(response->uuid_user, response->uuid_team);
    else
        return -1;
    return 0;
}
