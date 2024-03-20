/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include <stdio.h>
#include "database.h"

static int check_database_file(database_t *database)
{
    FILE *file;

    if (access(database->path_to_database, F_OK) == -1) {
        file = fopen(database->path_to_database, "w");
        if (file == NULL)
            return 0;
        fclose(file);
    }
    return 1;
}

static void restore_command(server_t *server, client_t *client, void *payload)
{
    for (int i = 0; i < NB_CMD; i++) {
        if (commands[i].code == ((raw_msg_t *) payload)->code) {
            commands[i].func(server, client, payload, 1);
            return;
        }
    }
}

static void read_database(server_t *server)
{
    FILE *file = fopen(server->database->path_to_database, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    client_t *client = malloc(sizeof(client_t));

    strcpy(client->context_team, UUID_NONE);
    strcpy(client->context_channel, UUID_NONE);
    strcpy(client->context_thread, UUID_NONE);
    if (file == NULL)
        return;
    while ((read = getline(&line, &len, file) > 0))
        restore_command(server, client, line);
    fclose(file);
}

static char *get_path(void)
{
    size_t len;
    char *final_path = NULL;
    char *path = getcwd(NULL, 0);

    len = strlen(path);
    len += path[strlen(path) - 1] != '/';
    len += strlen(PATH_TO_DATABASE);
    final_path = malloc(sizeof(char) * (len + 1));
    strcpy(final_path, path);
    if (path[strlen(path) - 1] != '/')
        strcat(final_path, "/");
    strcat(final_path, PATH_TO_DATABASE);
    return final_path;
}

void database_init(server_t *server)
{
    char *path = get_path();

    server->database = malloc(sizeof(database_t));
    server->database->path_to_database = path;
    server->database->users = NULL;
    server->database->teams = NULL;
    if (check_database_file(server->database) == 0)
        return;
    read_database(server);
}
