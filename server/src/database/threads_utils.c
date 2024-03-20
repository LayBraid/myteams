/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

int find_thread(channel_t *channel, char *uuid)
{
    thread_t *tmp = channel->threads;

    if (channel->threads == NULL)
        return 0;
    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return 0;
    return 1;
}

int find_thread_by_name(channel_t *channel, char *name)
{
    thread_t *tmp = channel->threads;

    if (channel->threads == NULL)
        return 0;
    while (tmp != NULL && strcmp(tmp->name, name) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return 0;
    return 1;
}

thread_t *get_thread(channel_t *channel, char *uuid)
{
    thread_t *tmp = channel->threads;

    if (channel->threads == NULL)
        return NULL;
    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return NULL;
    return tmp;
}
