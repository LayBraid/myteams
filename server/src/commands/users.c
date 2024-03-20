/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int response(server_t *server, client_t *client)
{
    s_users_response_t *response = malloc(sizeof(s_users_response_t));
    response->code = USERS_RESPONSE;
    response->status_code = REQUEST_OK;

    user_t *tmp = server->database->users;
    while (tmp) {
        strcpy(response->uuid, tmp->uuid);
        strcpy(response->username, tmp->username);
        response->error_code = tmp->is_connected;
        write(client->socket.fd, response, sizeof(s_users_response_t));
        tmp = tmp->next;
        usleep(20);
    }
    free(response);
    return 0;
}

static int response_not_connected(client_t const *client)
{
    s_users_response_t *response = malloc(sizeof(s_users_response_t));

    strcpy(response->uuid, client->uuid);
    strcpy(response->username, "");
    response->code = USERS_RESPONSE;
    response->status_code = REQEST_UNAUTHORIZED;
    response->error_code = NOT_CONNECTED;

    write(client->socket.fd, response, sizeof(s_users_response_t));
    free(response);
    return 0;
}

int users(server_t *server, client_t *client, void *payload, int restore)
{
    if (!restore && !client->logged) return response_not_connected(client);

    (void) restore;
    (void) payload;

    return response(server, client);
}
