/*
** EPITECH PROJECT, 2023
** server
** File description:
** subscription_writers
*/

#include "database.h"

int write_subscribe(database_t *database, s_subscribe_request_t *req)
{
    FILE *file = fopen(database->path_to_database, "a");

    if (file == NULL)
        return 0;
    fwrite(req, sizeof(s_subscribe_request_t), 1, file);
    fwrite("\n", 1, 1, file);
    fclose(file);
    return 1;
}

int write_unsubscribe(database_t *database, s_unsub_request_t *req)
{
    FILE *file = fopen(database->path_to_database, "a");

    if (file == NULL)
        return 0;
    fwrite(req, sizeof(s_unsub_request_t), 1, file);
    fwrite("\n", 1, 1, file);
    fclose(file);
    return 1;
}
