/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

static int add_message_to_user(user_t *user, s_send_request_t *message)
{
    message_t *tmp = user->messages;
    message_t *new = malloc(sizeof(message_t));

    strcpy(new->sender_uuid, message->uuid_sender);
    strcpy(new->receiver_uuid, message->uuid_receiver);
    strcpy(new->message, message->msg);
    new->timestamp = message->timestamp;
    new->next = NULL;
    if (user->messages == NULL) {
        user->messages = new;
        return 1;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return 1;
}

int add_message(database_t *database, s_send_request_t *message, int restore)
{
    user_t *sender = get_user(database, message->uuid_sender);
    user_t *receiver;

    if (!DB_FIND_USER(database, message->uuid_receiver)) return -1;
    receiver = get_user(database, message->uuid_receiver);
    if (!restore) write_message(database, message);
    add_message_to_user(sender, message);
    add_message_to_user(receiver, message);
    return 1;
}

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

static void uuid(message_t *new_message,
s_create_request_t *request, int restore)
{
    if (restore)
        strcpy(new_message->message_uuid, request->thread_uuid);
    else {
        strcpy(new_message->message_uuid, generate_uuid());
        strcpy(request->thread_uuid, new_message->message_uuid);
    }
}

char *add_message_to_thread(database_t *database, s_create_request_t *message,
thread_t *thread, int restore)
{
    message_t *tmp = thread->messages;
    message_t *new = malloc(sizeof(message_t));

    strcpy(new->sender_uuid, message->second_arg);
    strcpy(new->message, message->first_arg);
    uuid(new, message, restore);
    new->timestamp = message->timestamp;
    new->next = NULL;
    if (!restore) write_create(database, format_request(message));
    if (thread->messages == NULL) {
        thread->messages = new;
        return new->message_uuid;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return new->message_uuid;
}
