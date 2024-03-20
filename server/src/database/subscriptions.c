/*
** EPITECH PROJECT, 2023
** server
** File description:
** subscriptions
*/

#include "database.h"

int is_user_sub(team_t *team, user_t *user)
{
    user_list_t *tmp = team->users_subscribed;

    if (tmp == NULL)
        return false;
    while (tmp) {
        if (strcmp(tmp->user->uuid, user->uuid) == 0) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

int sub_user(team_t *team, user_t *user)
{
    user_list_t *tmp = team->users_subscribed;
    user_list_t *new = malloc(sizeof(user_list_t));
    new->user = user;
    new->next = NULL;

    if (tmp == NULL) {
        team->users_subscribed = new;
        return 0;
    }

    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return 0;
}

static int unsub_prereqs(team_t *team, char const *uuid)
{
    user_list_t *tmp = team->users_subscribed;

    if (tmp == NULL)
        return 1;
    if (tmp->next == NULL) {
        free(tmp);
        team->users_subscribed = NULL;
        return 1;
    }
    if (strcmp(tmp->user->uuid, uuid) == 0) {
        user_list_t *next = tmp->next;
        free(tmp);
        team->users_subscribed = next;
        return 1;
    }
    return 0;
}

int unsub_user(team_t *team, user_t *user)
{
    if (unsub_prereqs(team, user->uuid) == 1)
        return 0;

    user_list_t *tmp = team->users_subscribed;

    while (tmp->next) {
        user_list_t *next = tmp->next;
        if (strcmp(next->user->uuid, user->uuid) == 0) {
            tmp->next = tmp->next->next;
            free(next);
            continue;
        }
        tmp = tmp->next;
    }
    return 0;
}
