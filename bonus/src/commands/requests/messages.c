/*
** EPITECH PROJECT, 2023
** playground
** File description:
** No file there , just an epitech header example
*/

#include "../../../include/command.h"

int messages(client_t *client, char **args, int fd)
{
    if (args[1] == NULL) {
        return -1;
    }

    (void) client;
    s_messages_request_t *request = malloc(sizeof(s_messages_request_t));

    request->code = MESSAGES_REQUEST;
    request->timestamp = time(0);

    strcpy(request->uuid_sender, client->uuid);
    strcpy(request->uuid_subject, args[1]);

    write(fd, request, sizeof(s_messages_request_t));
    free(request);
    return 0;
}
