/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#ifndef SERVER_STRUCT_H
    #define SERVER_STRUCT_H

    #include "client.h"

    #define NB_CMD 14

typedef struct message_s message_t;
typedef struct user_s user_t;
typedef struct user_list_s user_list_t;
typedef struct thread_s thread_t;
typedef struct team_s team_t;
typedef struct channel_s channel_t;
typedef struct command command_t;
typedef struct database_s database_t;

struct message_s {
    char message_uuid[37];
    char sender_uuid[37];
    char receiver_uuid[37];
    char message[1024];
    time_t timestamp;
    struct message_s *next;
};

struct user_s {
    char uuid[37];
    char username[32];
    bool is_connected;
    message_t *messages;
    user_t *next;
};

struct user_list_s {
    user_t *user;
    user_list_t *next;
};

struct thread_s {
    char uuid[37];
    char uuid_creator[37];
    char channel_uuid[37];
    char team_uuid[37];
    char name[32];
    char description[255];
    char body[512];
    message_t *messages;
    time_t timestamp;
    thread_t *next;
};

struct channel_s {
    char uuid[37];
    char uuid_creator[37];
    char team_uuid[37];
    char *name;
    char *description;
    message_t *messages;
    thread_t *threads;
    channel_t *next;
};

struct team_s {
    char uuid[37];
    char name[32];
    char description[255];
    user_list_t *users_subscribed;
    channel_t *channels;
    team_t *next;
};

struct command {
    int code;
    int (*func)(client_t *, void *, int);
};

struct database_s {
    char *path_to_database;
    user_t *users;
    team_t *teams;
    command_t commands[NB_CMD];
};

typedef struct server_s server_t;

struct server_s {
    socket_t *control_socket;
    client_t *client_list;
    fd_set readfds;
    database_t *database;
};

#endif //SERVER_STRUCT_H
