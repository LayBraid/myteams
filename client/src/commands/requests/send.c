/*
** EPITECH PROJECT, 2023
** playground
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

void copy_message(s_send_request_t *request, char **args)
{
    for (int i = 2; args[i] != NULL; i++) {
        if (i != 2)
            strcat(request->msg, strdup(" "));
        strcat(request->msg, args[i]);
    }
}

int send_command(client_t *client, char **args, int fd)
{
    if (args[1] == NULL || args[2] == NULL)
        return -1;

    (void) client;
    s_send_request_t *request = malloc(sizeof(s_send_request_t));

    request->code = SEND_REQUEST;
    request->timestamp = time(0);

    strcpy(request->uuid_sender, client->uuid);
    strcpy(request->uuid_receiver, args[1]);
    copy_message(request, args);
    write(fd, request, sizeof(s_send_request_t));
    free(request);
    return 0;
}
