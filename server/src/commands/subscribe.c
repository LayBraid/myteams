/*
** EPITECH PROJECT, 2023
** server
** File description:
** subscribe
*/

#include "command.h"

static int response(client_t *client, team_t *team)
{
    s_subscribe_response_t *res = malloc(sizeof(s_subscribe_response_t));
    res->code = SUBSCRIBE_RESPONSE;
    res->status_code = REQUEST_OK;
    res->error_code = NO_ERROR;

    strcpy(res->uuid_user, client->uuid);
    strcpy(res->uuid_team, team->uuid);
    write(client->socket.fd, res, sizeof(s_subscribe_response_t));

    free(res);
    return 0;
}

static int response_ko(client_t const *client)
{
    s_subscribe_response_t *res = malloc(sizeof(s_subscribe_response_t));
    res->code = SUBSCRIBE_RESPONSE;
    res->status_code = REQUEST_KO;
    res->error_code = ALREADY_CONNECTED;
    write(client->socket.fd, res, sizeof(s_subscribe_response_t));
    free(res);
    return 0;
}

static int response_not_connected(client_t const *client)
{
    s_subscribe_response_t *response = malloc(sizeof(s_subscribe_response_t));

    strcpy(response->uuid_user, UUID_NONE);
    strcpy(response->uuid_team, UUID_NONE);
    response->code = SUBSCRIBE_RESPONSE;
    response->status_code = REQEST_UNAUTHORIZED;
    response->error_code = NOT_CONNECTED;

    write(client->socket.fd, response, sizeof(s_subscribe_response_t));
    free(response);
    return 0;
}

int subscribe(server_t *server, client_t *client, void *payload, int restore)
{
    if (!restore && !client->logged) return response_not_connected(client);

    s_subscribe_request_t *request = UNMARSHALL(subscribe_request) payload;
    team_t *team = get_team(server->database, request->uuid_team);

    if (!team) return response_ko(client);
    if (is_user_sub(team, get_user(server->database, request->uuid_user)))
        return response_ko(client);
    sub_user(team, get_user(server->database, request->uuid_user));
    if (restore) return 0;
    write_subscribe(server->database, request);
    return response(client, team);
}
