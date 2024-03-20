/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

int logout_response(client_t *client, void *payload)
{
    (void) client;
    s_logout_response_t *response = UNMARSHALL(logout_response) payload;

    if (response->status_code == REQUEST_OK) {
        client_event_logged_out(response->uuid, response->username);
    } else {
        client_error_unauthorized();
    }
    return 0;
}
