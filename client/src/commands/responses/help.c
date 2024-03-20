/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

int help_response(client_t *client, void *payload)
{
    (void) client;
    s_help_response_t *response = UNMARSHALL(help_response) payload;

    if (response->status_code == REQUEST_KO &&
        response->error_code == NOT_CONNECTED) {
        client_error_unauthorized();
        return 1;
    }
    printf("See the documentation for more information.\n");
    return 0;
}
