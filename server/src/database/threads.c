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

static void uuid(thread_t *new_thread,
s_create_request_t *request, int restore)
{
    if (restore)
        strcpy(new_thread->uuid, request->thread_uuid);
    else {
        strcpy(new_thread->uuid, generate_uuid());
        strcpy(request->thread_uuid, new_thread->uuid);
    }
}

char *add_thread(database_t *database, channel_t *channel,
s_create_request_t *request, int restore)
{
    thread_t *tmp = channel->threads;
    thread_t *new_thread = malloc(sizeof(thread_t));

    uuid(new_thread, request, restore);
    strcpy(new_thread->uuid_creator, request->uuid);
    strcpy(new_thread->name, request->first_arg);
    strcpy(new_thread->channel_uuid, request->channel_uuid);
    strcpy(new_thread->team_uuid, request->team_uuid);
    new_thread->messages = NULL;
    new_thread->timestamp = time(NULL);
    new_thread->next = NULL;
    if (!restore) write_create(database, format_request(request));
    if (channel->threads == NULL) {
        channel->threads = new_thread;
        return new_thread->uuid;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_thread;
    return new_thread->uuid;
}
