/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "client.h"
#include "database.h"

void push(client_t **list, client_t *new_sock)
{
    if (*list == NULL) {
        *list = new_sock;
        return;
    }
    client_t *tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_sock;
    true;
}

void delete(client_t *to_delete, client_t **list)
{
    client_t *tmp = *list;

    if (*list == NULL)
        return;
    if (tmp == to_delete) {
        *list = tmp->next;
        free(tmp);
        return;
    }
    while (tmp->next) {
        if (tmp->next == to_delete) {
            tmp->next = tmp->next->next;
            free(to_delete);
            return;
        }
        tmp = tmp->next;
    }
}

client_t *get_client(client_t **list, int fd)
{
    client_t *tmp = *list;
    while (tmp) {
        if (tmp->socket.fd == fd) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

client_t *new_client(int fd)
{
    client_t *new_client = malloc(sizeof(client_t));
    int addr_size = sizeof(new_client->socket.saddr);

    if (fd > 0)
        new_client->socket.fd = accept(fd,
        (struct sockaddr *)&new_client->socket.saddr,
        (socklen_t *)&addr_size);
    new_client->logged = false;
    new_client->next = NULL;
    new_client->data_socket = NULL;
    new_client->status = NONE;
    new_client->rec = NULL;
    new_client->send = NULL;
    new_client->data_socket = NULL;
    strcpy(new_client->context_team, UUID_NONE);
    strcpy(new_client->context_channel, UUID_NONE);
    strcpy(new_client->context_thread, UUID_NONE);
    new_client->username[0] = '\0';
    new_client->uuid[0] = '\0';
    return new_client;
}

int delete_client(server_t *server, client_t *to_delete,
client_t **list, bool force)
{
    user_t *tmp_user = get_user(server->database, to_delete->uuid);
    s_logout_request_t *request = malloc(sizeof(s_logout_request_t));

    if (tmp_user && force == false) {
        request->code = LOGOUT_REQUEST;
        strcpy(request->uuid, to_delete->uuid);
        logout(server, to_delete, request, 0);
    }
    if (tmp_user)
        tmp_user->is_connected = false;
    if (to_delete->data_socket)
        delete_data_socket(to_delete->data_socket);
    close(to_delete->socket.fd);
    delete(to_delete, list);
    return 0;
}
