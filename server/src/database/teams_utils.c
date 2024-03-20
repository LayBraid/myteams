/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

int find_team(database_t *database, char *uuid)
{
    team_t *tmp = database->teams;

    if (database == NULL) return 0;
    if (database->teams == NULL) return 0;
    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return 0;
    return 1;
}

int find_team_by_name(database_t *database, char *name)
{
    team_t *tmp = database->teams;

    if (database == NULL) return 0;
    if (database->teams == NULL) return 0;
    while (tmp != NULL) {
        if (strcmp(tmp->name, name) == 0) return 1;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return 0;
    return 0;
}

team_t *get_team(database_t *database, char *uuid)
{
    team_t *tmp = database->teams;

    if (database->teams == NULL)
        return NULL;
    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return NULL;
    return tmp;
}

team_t *get_subscribed_teams(team_t *team, char *user_uuid)
{
    if (team == NULL)
        return NULL;
    while (team != NULL) {
        if (is_user_in_team(team, user_uuid) == true)
            return team;
        team = team->next;
    }
    return NULL;
}
