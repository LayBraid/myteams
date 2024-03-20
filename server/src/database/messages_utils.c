/*
** EPITECH PROJECT, 2023
** server
** File description:
** messages_utils
*/

#include "database.h"

message_t *get_message(message_t *msg, char *sender_uuid, char *subject_uuid)
{
    if (msg == NULL)
        return NULL;

    while (msg != NULL) {
        if ((strcmp(msg->sender_uuid, sender_uuid) == 0
        && strcmp(msg->receiver_uuid, subject_uuid) == 0)
        || (strcmp(msg->sender_uuid, subject_uuid) == 0
        && strcmp(msg->receiver_uuid, sender_uuid) == 0))
            return msg;
        msg = msg->next;
    }
    return NULL;
}

message_t *get_message_in_thread(thread_t *thread, char *uuid)
{
    message_t *tmp = thread->messages;

    while (tmp != NULL) {
        if (strcmp(tmp->message_uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
