/*
** EPITECH PROJECT, 2023
** server
** File description:
** ex00
*/

#include "command.h"

static int response(client_t *client, team_t *team)
{
    s_list_response_t *response = malloc(sizeof(s_list_response_t));

    response->code = LIST_RESPONSE;
    response->status_code = REQUEST_OK;
    response->context = CONTEXT_NONE;
    response->error_code = NO_ERROR;
    strcpy(response->team_uuid, team->uuid);
    strcpy(response->name, team->name);
    strcpy(response->description, team->description);
    write(client->socket.fd, response, sizeof(s_list_response_t));
    free(response);
    return 1;
}

int list_none(server_t *server, client_t *client)
{
    team_t *team = server->database->teams;

    if (team == NULL) return 0;
    while (team != NULL) {
        response(client, team);
        team = team->next;
        usleep(20);
    }
    return 1;
}
