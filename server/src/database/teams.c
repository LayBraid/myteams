/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

static void uuid(team_t *new_team, s_create_request_t *request, int restore)
{
    if (restore)
        strcpy(new_team->uuid, request->team_uuid);
    else {
        strcpy(new_team->uuid, generate_uuid());
        strcpy(request->team_uuid, new_team->uuid);
    }
}

char *add_team(database_t *database, s_create_request_t *request, int restore)
{
    team_t *tmp = database->teams;
    team_t *new_team = malloc(sizeof(team_t));

    uuid(new_team, request, restore);
    strcpy(new_team->name, request->first_arg);
    strcpy(new_team->description, request->second_arg);
    new_team->channels = NULL;
    new_team->next = NULL;
    if (!restore) write_create(database, request);
    if (database->teams == NULL) {
        database->teams = new_team;
        return new_team->uuid;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_team;
    return new_team->uuid;
}
