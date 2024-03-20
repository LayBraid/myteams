/*
** EPITECH PROJECT, 2023
** client
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

int occurence(char *str, char c);
void remove_trailing(char *str);

char **single_arg(char *arg)
{
    char **args = malloc(sizeof(char *) * 2);

    args[0] = strdup(arg);
    args[1] = NULL;
    return args;
}

char *unwrap(char *str)
{
    char *new;

    if (str[0] == '"' && str[strlen(str) - 1] == '"') {
        new = malloc(sizeof(char) * (strlen(str) - 1));
        strncpy(new, str + 1, strlen(str) - 2);
        new[strlen(str) - 2] = '\0';
    } else
        new = strdup(str);
    return new;
}

char *trim_space(char *str)
{
    char *end;

    while (*str == ' ')
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && *end == ' ')
        end--;

    end[1] = '\0';

    return str;
}

int full_space(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ' && str[i] != '\"')
            return 0;
    return 1;
}

char **unmarshall2(char *rec)
{
    char **args = malloc(sizeof(char *) * ((occurence(rec, '\"') / 2) + 3));
    char *token = strtok(rec, "\"");
    int i = 0;

    if (token == NULL)
        return single_arg(rec);
    while (token) {
        if (!full_space(token)) {
            args[i] = unwrap(trim_space(strdup(token)));
            args[i][strlen(args[i])] = '\0';
            remove_trailing(args[i]);
            i++;
        }
        token = strtok(NULL, "\"");
    }
    args[i] = NULL;
    return args;
}
