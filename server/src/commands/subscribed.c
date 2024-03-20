/*
** EPITECH PROJECT, 2023
** server
** File description:
** subscribed
*/

#include "command.h"

static int rteams(team_t *tmp, client_t *client, s_subscribed_response_t *res)
{
    int at_least_one_team = false;
    while (tmp) {
        team_t *team = get_subscribed_teams(tmp, client->uuid);
        if (team == NULL) break;
        at_least_one_team = true;
        strcpy(res->uuid, tmp->uuid);
        strcpy(res->name, tmp->name);
        strcpy(res->description, tmp->description);
        write(client->socket.fd, res, sizeof(s_subscribed_response_t));
        tmp = team->next;
        usleep(20);
    }
    return at_least_one_team;
}

static int rusers(server_t *serv, team_t *team,
client_t *client, s_subscribed_response_t *res)
{
    user_list_t *tmp = team->users_subscribed;
    if (tmp == NULL)
        return false;
    while (tmp) {
        user_t *usr = tmp->user;
        strcpy(res->uuid, usr->uuid);
        strcpy(res->name, usr->username);
        strcpy(res->description, "");
        res->error_code = NO_ERROR;
        client_t *corresponding_client = find_client(serv, usr->uuid);
        res->logged = corresponding_client && corresponding_client->logged;
        write(client->socket.fd, res, sizeof(s_subscribed_response_t));
        tmp = tmp->next;
        usleep(20);
    }
    return true;
}

static int response(server_t *server, client_t *client, team_t *team)
{
    (void) client;
    s_subscribed_response_t *response = malloc(sizeof(s_subscribed_response_t));

    response->code = SUBSCRIBED_RESPONSE;
    response->status_code = REQUEST_OK;

    team_t *tmp = server->database->teams;
    if ((team == NULL && !rteams(tmp, client, response))
    || (team != NULL && !rusers(server, team, client, response))) {
        response->error_code = NOT_FOUND;
        write(client->socket.fd, response, sizeof(s_subscribed_response_t));
    }

    free(response);
    return 0;
}

static int response_not_connected(client_t const *client)
{
    s_subscribed_response_t *response = malloc(sizeof(s_subscribed_response_t));

    strcpy(response->name, "");
    strcpy(response->description, "");
    strcpy(response->uuid, UUID_NONE);
    response->code = SUBSCRIBED_RESPONSE;
    response->status_code = REQEST_UNAUTHORIZED;
    response->error_code = NOT_CONNECTED;
    response->logged = 0;

    write(client->socket.fd, response, sizeof(s_subscribed_response_t));
    free(response);
    return 0;
}

int subscribed(server_t *server, client_t *client, void *payload, int restore)
{
    if (!restore && !client->logged) return response_not_connected(client);

    s_subscribed_request_t *request = UNMARSHALL(subscribed_request) payload;

    if (!DB_FIND_USER(server->database, request->uuid))
        return -1;

    team_t *team = get_team(server->database, request->team_uuid);

    if (restore) return 0;
    return response(server, client, team);
}
