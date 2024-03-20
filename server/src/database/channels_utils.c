/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

int find_channel(team_t *team, char *uuid)
{
    channel_t *tmp = team->channels;

    if (team->channels == NULL)
        return 0;
    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return 0;
    return 1;
}

int find_channel_by_name(team_t *team, char *name)
{
    channel_t *tmp = team->channels;

    if (team->channels == NULL)
        return 0;
    while (tmp != NULL && strcmp(tmp->name, name) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return 0;
    return 1;
}

channel_t *get_channel(team_t *team, char *uuid)
{
    channel_t *tmp = team->channels;

    if (team->channels == NULL)
        return NULL;
    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return NULL;
    return tmp;
}
