/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int get_context(s_use_request_t *request)
{
    if (strcmp(request->team_uuid, UUID_NONE) != 0
        && strcmp(request->channel_uuid, UUID_NONE) != 0
        && strcmp(request->thread_uuid, UUID_NONE) != 0)
        return CONTEXT_THREAD;
    if (strcmp(request->team_uuid, UUID_NONE) != 0
        && strcmp(request->channel_uuid, UUID_NONE) != 0
        && strcmp(request->thread_uuid, UUID_NONE) == 0)
        return CONTEXT_CHANNEL;
    if (strcmp(request->team_uuid, UUID_NONE) != 0
        && strcmp(request->channel_uuid, UUID_NONE) == 0
        && strcmp(request->thread_uuid, UUID_NONE) == 0)
        return CONTEXT_TEAM;
    return CONTEXT_NONE;
}

int local_context(client_t *client)
{
    if (strcmp(client->context_team, UUID_NONE) != 0 &&
        strcmp(client->context_channel, UUID_NONE) != 0 &&
        strcmp(client->context_thread, UUID_NONE) != 0)
        return CONTEXT_THREAD;
    if (strcmp(client->context_team, UUID_NONE) != 0 &&
        strcmp(client->context_channel, UUID_NONE) != 0 &&
        strcmp(client->context_thread, UUID_NONE) == 0)
        return CONTEXT_CHANNEL;
    if (strcmp(client->context_team, UUID_NONE) != 0 &&
        strcmp(client->context_channel, UUID_NONE) == 0 &&
        strcmp(client->context_thread, UUID_NONE) == 0)
        return CONTEXT_TEAM;
    return CONTEXT_NONE;
}
