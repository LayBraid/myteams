/*
** EPITECH PROJECT, 2023
** server
** File description:
** ex00
*/

#include "command.h"

static int response(client_t *client, team_t *team)
{
    s_info_response_t *response = malloc(sizeof(s_info_response_t));

    response->code = INFO_RESPONSE;
    response->status_code = REQUEST_OK;
    response->context = CONTEXT_TEAM;
    response->error_code = NO_ERROR;
    response->user_status = client->logged;
    strcpy(response->team_uuid, team->uuid);
    strcpy(response->name, team->name);
    strcpy(response->description, team->description);
    write(client->socket.fd, response, sizeof(s_info_response_t));
    free(response);
    return 1;
}

static int not_found(client_t *client)
{
    s_info_response_t *response = malloc(sizeof(s_info_response_t));

    response->code = INFO_RESPONSE;
    response->status_code = REQUEST_KO;
    response->error_code = NOT_FOUND;
    response->context = CONTEXT_TEAM;
    write(client->socket.fd, response, sizeof(s_info_response_t));
    return 0;
}

int info_team(server_t *server, client_t *client)
{
    team_t *team = get_team(server->database, client->context_team);

    if (team == NULL) return not_found(client);
    return response(client, team);
}
