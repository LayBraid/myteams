/*
** EPITECH PROJECT, 2023
** client
** File description:
** subscribed
*/

#include "command.h"

int subscribed_response(client_t *client, void *payload)
{
    (void) client;
    s_subscribed_response_t *res = UNMARSHALL(subscribed_response) payload;

    if (res->status_code == REQEST_UNAUTHORIZED
        && res->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 0;
    }
    if (res->error_code == NOT_FOUND)
        return 0;
    if (res->description[0] == '\0') {
        client_print_users(res->uuid,res->name,res->logged);
        return 0;
    }
    client_print_team(res->uuid,res->name,res->description);
    return 0;
}
