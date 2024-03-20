/*
** EPITECH PROJECT, 2023
** test
** File description:
** No file there , just an epitech header example
*/

#include "../../include/client.h"
#include "../../include/command.h"

const commands_t commands[NB_CMD] = {
        {"/login", login},
        {"/logout", logout},
        {"/send", send_command},
        {"/messages", messages},
        {"/use", use},
        {"/user", user},
        {"/create", create},
        {"/users", users},
        {"/info", info},
        {"/list", list}
};

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        if (tab[i])
            free(tab[i]);
    free(tab);
}

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

void remove_trailing(char *str)
{
    if (*str == '\0')
        return;
    if (*str == '\r' || *str == '\n')
        *str = '\0';
    remove_trailing(str + 1);
}

char **single_arg(char *arg)
{
    char **args = malloc(sizeof(char *) * 2);

    args[0] = strdup(arg);
    args[1] = NULL;
    return args;
}

char **unmarshall(char *rec)
{
    char **args = malloc(sizeof(char *) * (occurence(rec, ' ') + 2));
    char *token = strtok(rec, " ");
    int i = 0;

    if (token == NULL)
        return single_arg(rec);
    while (token) {
        args[i] = strdup(token);
        args[i][strlen(args[i])] = '\0';
        remove_trailing(args[i]);
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    return args;
}

void exe_cmd(client_t *client, char *got, int fd)
{
    char **args = unmarshall(got);
    printf("got: %s\n", args[0]);
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
