/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#ifndef SERVER_DATABASE_H
    #define SERVER_DATABASE_H

    #include "unistd.h"
    #include "string.h"
    #include "struct.h"
    #include "command.h"
    #include "proto.h"

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_MESSAGE_LENGTH 512

    #define PATH_TO_DATABASE "database.txt"

    #define UUID_NONE "00000000-0000-0000-0000-000000000000"

    #define NO_RESTORE(restore, exe) \
        if (restore == 0) { \
            exe; \
        }

    #define NO_RESTORE_ELSE(restore, exe, other) \
        if (restore == 0) { \
            exe; \
        } else { \
            other; \
        }

void database_init(server_t *server);
void write_database(database_t *database, void *payload);

int add_user(database_t *database, s_login_request_t *user, int restore);
int remove_user(database_t *database, s_logout_request_t *user, int restore);
int find_user(database_t *database, char *uuid);
int find_user_by_name(database_t *database, char *username);
char *get_user_uuid(database_t *database, char *username);
user_t *get_user(database_t *database, char *uuid);
int count_users(database_t *database);
int add_message(database_t *database, s_send_request_t *message, int restore);
int find_team(database_t *database, char *uuid);
int find_team_by_name(database_t *database, char *name);
team_t *get_team(database_t *database, char *uuid);
int find_channel(team_t *team, char *uuid);
int find_channel_by_name(team_t *team, char *name);
channel_t *get_channel(team_t *team, char *uuid);
int find_thread(channel_t *channel, char *uuid);
int find_thread_by_name(channel_t *channel, char *name);
thread_t *get_thread(channel_t *channel, char *uuid);
char *add_team(database_t *database, s_create_request_t *request, int restore);
char *add_channel(database_t *database, s_create_request_t *create,
    int restore, char *team_uuid);
char *add_thread(database_t *database, channel_t *channel,
    s_create_request_t *request, int restore);
char *add_message_to_thread(database_t *database, s_create_request_t *message,
    thread_t *thread, int restore);
message_t *get_message_in_thread(thread_t *thread, char *uuid);
int is_user_in_team(team_t *team, char *user_uuid);
team_t *get_subscribed_teams(team_t *team, char *user_uuid);

int write_user(database_t *database, s_login_request_t *user);
int write_logout(database_t *database, s_logout_request_t *user);
int write_message(database_t *database, s_send_request_t *message);
int write_context(database_t *database, s_use_request_t *context);
int write_create(database_t *database, s_create_request_t *create);
int write_subscribe(database_t *database, s_subscribe_request_t *req);
int write_unsubscribe(database_t *database, s_unsub_request_t *req);

    #define DB_ADD(database, payload) write_database(database, payload)

    #define DB_ADD_USER(db, u, res) add_user(db, u, res)
    #define DB_FIND_USER(database, uuid) find_user(database, uuid)
    #define DB_FIND_USER_BY_NAME(database, username) \
        find_user_by_name(database, username)
    #define DB_ANY_FIND_USER(database, uuid, username) \
        find_user(database, uuid) || find_user_by_name(database, username)
    #define DB_GET_USER(database, uuid) get_user(database, uuid)

#endif //SERVER_DATABASE_H
