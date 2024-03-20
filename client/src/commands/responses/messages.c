/*
** EPITECH PROJECT, 2023
** client
** File description:
** send
*/

#include "command.h"

int messages_response(client_t *client, void *payload)
{
    (void) client;
    s_messages_response_t *response = UNMARSHALL(messages_response) payload;

    if (response->status_code == REQEST_UNAUTHORIZED
        && response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 0;
    }

    client_private_message_print_messages(
    response->uuid_sender,
response->timestamp,
response->msg);
    return 0;
}
