/*
** EPITECH PROJECT, 2023
** client
** File description:
** ex00
*/

#include "command.h"

char **unmarshall2(char *rec);

int occurence(char *str, char c)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0') {
        if (str[i] == c)
            count++;
        i++;
    }
    return count;
}

void exe_cmd(client_t *client, int fd)
{
    char *cmd = get_next_cmd(client->buff);
    if (!cmd) return;
    char **args = unmarshall2(cmd);
    if (!args[0])
        return;
    for (int i = 0; i < NB_CMD; i++) {
        if (strcmp(args[0], commands[i].identifier) == 0) {
            commands[i].func(client, args, fd);
            free_tab(args);
            return;
        }
    }
}

bool handle(client_t *client)
{
    raw_msg_t *raw_msg = (raw_msg_t *)client->data;

    for (int i = 0; i < NB_CMD; i++) {
        if (raw_msg->code == responses[i].code) {
            responses[i].func(client, client->data);
            client->data = NULL;
            return true;
        }
    }
    client->data = NULL;
    return false;
}

int exe_response(client_t *client)
{
    if (!client->data)
        return 0;
    bool success = handle(client);

    if (!success)
        printf("CLIENT: 500 Unknown command.\n");
    return 0;
}

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        if (tab[i])
            free(tab[i]);
    free(tab);
}
