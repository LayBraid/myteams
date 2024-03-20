/*
** EPITECH PROJECT, 2023
** teams
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int response(server_t *server, client_t *client, int created)
{
    client_t *tmp = server->client_list;
    s_login_response_t *response = malloc(sizeof(s_login_response_t));

    response->code = LOGIN_RESPONSE;
    response->error_code = NO_ERROR;
    strcpy(response->uuid, client->uuid);
    strcpy(response->username, client->username);
    response->status_code = REQUEST_OK;
    if (created)
        server_event_user_created(client->uuid, client->username);
    server_event_user_logged_in(client->uuid);
    while (tmp) {
        if (tmp->logged)
            write(tmp->socket.fd, response, sizeof(s_login_response_t));
        tmp = tmp->next;
    }
    free(response);
    return 0;
}

static int simple_connection(server_t *server, client_t *client,
s_login_request_t *request)
{
    char *uuid = get_user_uuid(server->database, request->username);
    user_t *user = get_user(server->database, uuid);

    if (uuid == NULL) return -1;
    client->logged = true;
    user->is_connected = true;
    strcpy(client->username, user->username);
    strcpy(client->uuid, user->uuid);
    return response(server, client, 0);
}

int login(server_t *server, client_t *client, void *payload, int restore)
{
    s_login_request_t *request = UNMARSHALL(login_request) payload;
    user_t *user = NULL;

    strcpy(client->username, request->username);
    if (!restore && client->uuid[0] == '\0')
        strcpy(client->uuid, generate_uuid());
    if (restore) strcpy(client->uuid, request->uuid);
    if (DB_ANY_FIND_USER(server->database, client->uuid, client->username))
        return simple_connection(server, client, request);
    strcpy(request->uuid, client->uuid);
    if (!add_user(server->database, request, restore)) return -1;
    user = get_user(server->database, client->uuid);
    if (!restore) user->is_connected = true;
    if (!restore) client->logged = true;
    if (restore) server_event_user_loaded(client->uuid, client->username);
    if (restore) return 0;
    return response(server, client, 1);
}
