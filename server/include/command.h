/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #define _GNU_SOURCE

    #include <fcntl.h>
    #include <sys/wait.h>
    #include "request.h"
    #include "my_uuid.h"
    #include "logging_server.h"
    #include "struct.h"
    #include "database.h"

    #define NOTIFY_CREATE(client) { \
    if (client) \
        write(client->socket.fd, response, sizeof(s_create_response_t)); \
}

    #define NOTIFY_SEND(x, size) { \
    if (x && x->logged) \
        write(x->socket.fd, response, size); \
}

/* COMMAND */
extern int login(server_t *, client_t *, void *, int);
extern int help(server_t *, client_t *, void *, int);
extern int logout(server_t *, client_t *, void *, int);
extern int users(server_t *server, client_t *client,
    void *payload, int restore);
extern int user(server_t *server, client_t *client, void *payload, int restore);
extern int use(server_t *server, client_t *client, void *payload, int restore);
extern int use_thread(server_t *server, client_t *client,
    s_use_request_t *request, int restore);
extern int use_channel(server_t *server, client_t *client,
    s_use_request_t *request, int restore);
extern int use_team(server_t *server, client_t *client,
    s_use_request_t *request, int restore);
extern int use_none(server_t *server, client_t *client,
    s_use_request_t *request, int restore);
extern int create(server_t *server, client_t *client,
    void *payload, int restore);
extern int messages(server_t *server, client_t *client, void *payload,
    int restore);
extern int create_none(server_t *server, client_t *client,
    s_create_request_t *request, int restore);
extern int create_team(server_t *server, client_t *client,
    s_create_request_t *request, int restore);
extern int create_channel(server_t *server, client_t *client,
    s_create_request_t *request, int restore);
extern int create_thread(server_t *server, client_t *client,
    s_create_request_t *request, int restore);
extern int send_command(server_t *server, client_t *client, void *payload,
    int restore);
extern int messages(server_t *server, client_t *client, void *payload,
    int restore);
int info(server_t *server, client_t *client, void *payload, int restore);
int info_none(server_t *server, client_t *client);
int info_team(server_t *server, client_t *client);
int info_channel(server_t *server, client_t *client);
int info_thread(server_t *server, client_t *client);
int list(server_t *server, client_t *client, void *payload, int restore);
int list_none(server_t *server, client_t *client);
int list_team(server_t *server, client_t *client);
int list_channel(server_t *server, client_t *client);
int list_thread(server_t *server, client_t *client);
int subscribe(server_t *server, client_t *client, void *payload, int restore);
int unsubscribe(server_t *server, client_t *client,
    void *payload, int restore);
int subscribed(server_t *server, client_t *client,
    void *payload, int restore);

int get_context(s_use_request_t *request);
int local_context(client_t *client);
client_t *find_client(server_t *server, char uuid[37]);
message_t *get_message(message_t *msg, char *sender_uuid, char *subject_uuid);
int is_user_sub(team_t *team, user_t *user);
int sub_user(team_t *team, user_t *user);
int unsub_user(team_t *team, user_t *user);

typedef struct commands_s {
    uint code;
    char *identifier;
    int (*func)(server_t *, client_t *, void *, int);
} commands_t;

extern const commands_t commands[NB_CMD];

#endif //COMMAND_H_
