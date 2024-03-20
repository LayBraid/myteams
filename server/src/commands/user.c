/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int response(client_t *client, user_t *user)
{
    s_user_response_t *response = malloc(sizeof(s_user_response_t));

    response->code = USER_RESPONSE;
    response->status_code = REQUEST_OK;
    response->error_code = !user->is_connected ?
    ALREADY_CONNECTED : NOT_CONNECTED;
    strcpy(response->uuid, user->uuid);
    strcpy(response->username, user->username);
    write(client->socket.fd, response, sizeof(s_user_response_t));
    free(response);
    return 0;
}

static int response_not_connected(client_t const *client)
{
    s_user_response_t *response = malloc(sizeof(s_user_response_t));

    strcpy(response->uuid, client->uuid);
    strcpy(response->username, "");
    response->code = USER_RESPONSE;
    response->status_code = REQEST_UNAUTHORIZED;
    response->error_code = NOT_CONNECTED;

    write(client->socket.fd, response, sizeof(s_user_response_t));
    free(response);
    return 0;
}

int user(server_t *server, client_t *client, void *payload, int restore)
{
    if (!restore && !client->logged) return response_not_connected(client);

    s_user_request_t *request = UNMARSHALL(user_request) payload;
    user_t *user = NULL;
    (void) restore;

    if (!DB_FIND_USER(server->database, request->uuid))
        return -1;
    user = get_user(server->database, request->uuid);
    if (!user) return -1;
    return response(client, user);
}
