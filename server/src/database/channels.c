/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

static s_create_request_t *format_request(s_create_request_t *request)
{
    if (strlen(request->team_uuid) == 0)
        strcpy(request->team_uuid, "00000000-0000-0000-0000-000000000000");
    if (strlen(request->channel_uuid) == 0)
        strcpy(request->channel_uuid, "00000000-0000-0000-0000-000000000000");
    if (strlen(request->thread_uuid) == 0)
        strcpy(request->thread_uuid, "00000000-0000-0000-0000-000000000000");
    return request;
}

static void uuid(channel_t *new_channel,
s_create_request_t *request, int restore)
{
    if (restore)
        strcpy(new_channel->uuid, request->channel_uuid);
    else {
        strcpy(new_channel->uuid, generate_uuid());
        strcpy(request->channel_uuid, new_channel->uuid);
    }
}

char *add_channel(database_t *database, s_create_request_t *create,
int restore, char *team_uuid)
{
    team_t *team = get_team(database, team_uuid);
    channel_t *tmp = team->channels;
    channel_t *new_channel = malloc(sizeof(channel_t));

    uuid(new_channel, create, restore);
    strcpy(new_channel->uuid_creator, create->uuid);
    strcpy(new_channel->team_uuid, team_uuid);
    new_channel->name = strdup(create->first_arg);
    new_channel->description = strdup(create->second_arg);
    new_channel->threads = NULL;
    new_channel->next = NULL;
    if (!restore) write_create(database, format_request(create));
    if (team->channels == NULL) {
        team->channels = new_channel;
        return new_channel->uuid;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_channel;
    return new_channel->uuid;
}
