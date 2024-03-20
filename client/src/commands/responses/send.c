/*
** EPITECH PROJECT, 2023
** client
** File description:
** send
*/

#include "command.h"

int send_response(client_t *client, void *payload)
{
    (void) client;
    s_send_response_t *response = UNMARSHALL(send_response) payload;

    if (response->status_code == REQEST_UNAUTHORIZED
        && response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 0;
    }

    if (strcmp(client->uuid, response->uuid_receiver) == 0)
        client_event_private_message_received(response->uuid_sender,
            response->msg);
    return 0;
}
