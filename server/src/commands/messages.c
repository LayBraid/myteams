/*
** EPITECH PROJECT, 2023
** MY_TEAMS
** File description:
** messages
*/

#include "command.h"

static int response(client_t *client, s_messages_request_t *req, user_t *sender)
{
    s_messages_response_t *response = malloc(sizeof(s_messages_response_t));
    message_t *tmp = sender->messages;

    response->code = MESSAGES_RESPONSE;
    response->status_code = REQUEST_OK;
    response->error_code = NO_ERROR;
    while (tmp) {
        message_t *msg = get_message(tmp, req->uuid_sender, req->uuid_subject);
        if (msg == NULL) break;
        response->timestamp = msg->timestamp;
        strcpy(response->msg, msg->message);
        strcpy(response->uuid_sender, msg->sender_uuid);
        strcpy(response->uuid_receiver, msg->receiver_uuid);
        write(client->socket.fd, response, sizeof(s_messages_response_t));
        tmp = msg->next;
        usleep(20);
    }
    free(response);
    return 0;
}

static int response_not_connected(client_t const *client)
{
    s_messages_response_t *response = malloc(sizeof(s_messages_response_t));

    strcpy(response->uuid_receiver, UUID_NONE);
    strcpy(response->uuid_sender, UUID_NONE);
    strcpy(response->msg, "");
    response->timestamp = time(0);
    response->code = MESSAGES_RESPONSE;
    response->status_code = REQEST_UNAUTHORIZED;
    response->error_code = NOT_CONNECTED;

    write(client->socket.fd, response, sizeof(s_messages_response_t));
    free(response);
    return 0;
}

int messages(server_t *server, client_t *client, void *payload, int restore)
{
    if (!restore && !client->logged) return response_not_connected(client);

    s_messages_request_t *request = UNMARSHALL(messages_request) payload;

    if (!DB_FIND_USER(server->database, request->uuid_subject))
        return -1;

    user_t *sender = get_user(server->database, request->uuid_sender);
    if (!sender)
        return -1;

    if (restore) return 0;
    return response(client, request, sender);
}
