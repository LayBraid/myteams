/*
** EPITECH PROJECT, 2023
** MY_TEAMS
** File description:
** send
*/

#include "command.h"

static int response(server_t *server, client_t *client,
s_send_request_t *request)
{
    s_send_response_t *response = malloc(sizeof(s_send_response_t));

    response->code = SEND_RESPONSE;
    response->error_code = NO_ERROR;
    response->status_code = REQUEST_OK;
    strcpy(response->uuid_receiver, request->uuid_receiver);
    strcpy(response->uuid_sender, request->uuid_sender);
    strcpy(response->msg, request->msg);
    response->timestamp = request->timestamp;
    NOTIFY_SEND(find_client(server, request->uuid_receiver),
        sizeof(s_send_response_t));
    NOTIFY_SEND(client, sizeof(s_send_response_t));
    free(response);
    return 0;
}

static int response_not_connected(client_t const *client)
{
    s_send_response_t *response = malloc(sizeof(s_send_response_t));

    strcpy(response->uuid_receiver, UUID_NONE);
    strcpy(response->uuid_sender, UUID_NONE);
    strcpy(response->msg, "");
    response->timestamp = time(0);
    response->code = SEND_RESPONSE;
    response->status_code = REQEST_UNAUTHORIZED;
    response->error_code = NOT_CONNECTED;

    write(client->socket.fd, response, sizeof(s_send_response_t));
    free(response);
    return 0;
}

int send_command(server_t *server, client_t *client, void *payload, int restore)
{
    if (!client->logged) response_not_connected(client);

    s_send_request_t *request = UNMARSHALL(send_request) payload;

    if (!DB_FIND_USER(server->database, request->uuid_receiver))
        return -1;

    if (!add_message(server->database, request, restore))
        return -1;

    if (restore) return 0;
    return response(server, client, request);
}
