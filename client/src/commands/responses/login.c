/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

int login_response(client_t *client, void *payload)
{
    (void) client;
    s_login_response_t *response = UNMARSHALL(login_response) payload;

    if (response->status_code == REQUEST_OK && client->uuid[0] == '\0')
        strcpy(client->uuid, response->uuid);
    client_event_logged_in(response->uuid, response->username);
    return 0;
}
