/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

int write_user(database_t *database, s_login_request_t *user)
{
    FILE *file = fopen(database->path_to_database, "a");

    if (file == NULL)
        return 0;
    fwrite(user, sizeof(s_login_request_t), 1, file);
    fwrite("\n", 1, 1, file);
    fclose(file);
    return 1;
}

int write_logout(database_t *database, s_logout_request_t *user)
{
    FILE *file = fopen(database->path_to_database, "a");

    if (file == NULL)
        return 0;
    fwrite(user, sizeof(s_logout_request_t), 1, file);
    fwrite("\n", 1, 1, file);
    fclose(file);
    return 1;
}

int write_message(database_t *database, s_send_request_t *message)
{
    FILE *file = fopen(database->path_to_database, "a");

    if (file == NULL)
        return 0;
    fwrite(message, sizeof(s_send_request_t), 1, file);
    fwrite("\n", 1, 1, file);
    fclose(file);
    return 1;
}

int write_context(database_t *database, s_use_request_t *context)
{
    FILE *file = fopen(database->path_to_database, "a");

    if (file == NULL)
        return 0;
    fwrite(context, sizeof(s_use_request_t), 1, file);
    fwrite("\n", 1, 1, file);
    fclose(file);
    return 1;
}

int write_create(database_t *database, s_create_request_t *create)
{
    FILE *file = fopen(database->path_to_database, "a");

    if (file == NULL)
        return 0;
    fwrite(create, sizeof(s_create_request_t), 1, file);
    fwrite("\n", 1, 1, file);
    fclose(file);
    return 1;
}
