/*
** EPITECH PROJECT, 2023
** client
** File description:
** users
*/

#include "command.h"

int users_response(client_t *client, void *payload)
{
    (void) client;
    s_users_response_t *res = UNMARSHALL(users_response) payload;

    if (res->status_code == REQEST_UNAUTHORIZED
    && res->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 0;
    }

    client_print_users(res->uuid, res->username, res->error_code);
    return 0;
}
