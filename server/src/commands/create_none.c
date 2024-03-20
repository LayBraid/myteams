/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

static int response(client_t *client, team_t *team)
{
    s_create_response_t *response = malloc(sizeof(s_create_response_t));

    if (!response) return -1;
    response->code = CREATE_RESPONSE;
    response->context = CONTEXT_NONE;
    response->status_code = REQUEST_OK;
    response->error_code = NO_ERROR;
    strcpy(response->name, team->name);
    strcpy(response->team_uuid, team->uuid);
    strcpy(response->description, team->description);
    server_event_team_created(team->uuid, team->name, client->uuid);
    write(client->socket.fd, response, sizeof(s_create_response_t));
    free(response);
    return 1;
}

static int response_already_exist(client_t *client)
{
    s_create_response_t *response = malloc(sizeof(s_create_response_t));

    if (!response) return -1;
    response->code = CREATE_RESPONSE;
    response->context = CONTEXT_NONE;
    response->status_code = REQUEST_KO;
    response->error_code = ALREADY_EXIST;
    write(client->socket.fd, response, sizeof(s_create_response_t));
    return 1;
}

int create_none(server_t *server, client_t *client,
s_create_request_t *request, int restore)
{
    char *uuid = NULL;
    team_t *team = NULL;
    (void) client;

    if (request->first_arg[0] == '\0' ||
        request->second_arg[0] == '\0') return -1;
    if (find_team_by_name(server->database, request->first_arg) == 1)
        return response_already_exist(client);
    uuid = add_team(server->database, request, restore);
    team = get_team(server->database, uuid);
    if (restore) return 1;
    return response(client, team);
}
