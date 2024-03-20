/*
** EPITECH PROJECT, 2023
** client
** File description:
** user
*/

#include "command.h"

int user_response(client_t *client, void *payload)
{
    (void) client;
    s_user_response_t *response = UNMARSHALL(user_response) payload;

    if (response->status_code == REQEST_UNAUTHORIZED
        && response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 0;
    }

    if (response->status_code == REQUEST_OK)
        client_print_user(
response->uuid,
response->username,
response->error_code);
    return 0;
}
