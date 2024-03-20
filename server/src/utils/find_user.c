/*
** EPITECH PROJECT, 2023
** server
** File description:
** find_user
*/

#include "command.h"

client_t *find_client(server_t *server, char uuid[37])
{
    client_t *tmp = server->client_list;

    if (uuid == NULL)
        return NULL;
    if (server->client_list == NULL)
        return NULL;

    while (tmp != NULL && strcmp(tmp->uuid, uuid) != 0)
        tmp = tmp->next;
    if (tmp == NULL)
        return NULL;
    return tmp;
}
