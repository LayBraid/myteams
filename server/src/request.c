/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "request.h"

bool handle(server_t *server, client_t *client)
{
    raw_msg_t *raw_msg = (raw_msg_t *)client->rec;

    for (int i = 0; i < NB_CMD; i++) {
        if (raw_msg->code == commands[i].code) {
            commands[i].func(server, client, client->rec, 0);
            client->rec = NULL;
            return true;
        }
    }
    client->rec = NULL;
    return false;
}

int handle_commands(server_t *server, client_t *client)
{
    if (!client->rec) {
        return 0;
    }
    bool success = handle(server, client);
    if (!success)
        printf("500 Unknown command.\n");
    return 0;
}
