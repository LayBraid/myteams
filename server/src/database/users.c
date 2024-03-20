/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "database.h"

int add_user(database_t *database, s_login_request_t *user, int restore)
{
    user_t *new = malloc(sizeof(user_t));
    user_t *tmp = database->users;

    strcpy(new->uuid, user->uuid);
    strcpy(new->username, user->username);
    new->is_connected = false;
    new->messages = NULL;
    new->next = NULL;
    if (!restore) write_user(database, user);
    if (database->users == NULL) {
        database->users = new;
        return 1;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return 1;
}

int remove_user(database_t *database, s_logout_request_t *user, int restore)
{
    user_t *tmp = database->users;
    user_t *prev = NULL;
    (void) restore;

    if (database->users == NULL)
        return 0;
    while (tmp != NULL && strcmp(tmp->uuid, user->uuid) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return 0;
    if (prev == NULL)
        database->users = tmp->next;
    else
        prev->next = tmp->next;
    free(tmp->uuid);
    free(tmp->username);
    free(tmp);
    return 1;
}
