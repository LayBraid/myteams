/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

int find_user(database_t *database, char *uuid)
{
    user_t *tmp = database->users;

    if (uuid == NULL)
        return 0;
    if (database->users == NULL)
        return 0;
    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return 0;
    return 1;
}

int find_user_by_name(database_t *database, char *username)
{
    user_t *tmp = database->users;

    if (database->users == NULL)
        return 0;
    while (tmp != NULL && strcmp(tmp->username, username) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return 0;
    return 1;
}

user_t *get_user(database_t *database, char *uuid)
{
    user_t *tmp = database->users;

    if (database->users == NULL)
        return NULL;
    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return NULL;
    return tmp;
}

char *get_user_uuid(database_t *database, char *username)
{
    user_t *tmp = database->users;

    if (database->users == NULL)
        return NULL;
    while (tmp != NULL && strcmp(tmp->username, username) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return NULL;
    return tmp->uuid;
}

int is_user_in_team(team_t *team, char *user_uuid)
{
    user_list_t *tmp = team->users_subscribed;

    if (tmp == NULL)
        return false;
    while (tmp != NULL && strcmp(tmp->user->uuid, user_uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return false;
    return true;
}
