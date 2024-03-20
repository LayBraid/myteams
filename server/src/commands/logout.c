/*
** EPITECH PROJECT, 2023
** teams
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int response(server_t *server, client_t *client)
{
    client_t *tmp = server->client_list;
    s_logout_response_t *response = malloc(sizeof(s_logout_response_t));

    response->code = LOGOUT_RESPONSE;
    response->error_code = NO_ERROR;
    response->status_code = REQUEST_OK;
    strcpy(response->uuid, client->uuid);
    strcpy(response->username, client->username);
    server_event_user_logged_out(client->uuid);
    write(client->socket.fd, response, sizeof(s_logout_response_t));
    while (tmp) {
        if (tmp->logged)
            write(tmp->socket.fd, response, sizeof(s_logout_response_t));
        tmp = tmp->next;
    }
    free(response);
    return 0;
}

static int response_not_connected(client_t *client)
{
    s_logout_response_t *response = malloc(sizeof(s_logout_response_t));

    response->code = LOGOUT_RESPONSE;
    response->status_code = REQUEST_KO;
    response->error_code = NOT_CONNECTED;
    strcpy(response->uuid, client->uuid);
    strcpy(response->username, client->username);
    write(client->socket.fd, response, sizeof(s_logout_response_t));
    return 0;
}

int logout(server_t *server, client_t *client, void *payload, int restore)
{
    s_logout_request_t *request = UNMARSHALL(logout_request) payload;
    user_t *user = NULL;

    if (!restore && client->uuid[0] == '\0')
        return response_not_connected(client);
    if (restore) return 0;
    if (!DB_FIND_USER(server->database, client->uuid))
        return -1;
    user = get_user(server->database, client->uuid);
    if (!user->is_connected) return response_not_connected(client);
    user->is_connected = false;
    client->logged = false;
    write_logout(server->database, request);
    return response(server, client);
}
