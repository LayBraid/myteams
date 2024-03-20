/*
** EPITECH PROJECT, 2023
** playground
** File description:
** No file there , just an epitech header example
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #define NB_CMD 14
    #define UUID_NONE "00000000-0000-0000-0000-000000000000"

    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdio.h>
    #include "../../libs/myteams/logging_client.h"
    #include "client.h"
    #include "stdbool.h"

extern int login(client_t *client, char **args, int fd);
extern int logout(client_t *client, char **args, int fd);
extern int send_command(client_t *client, char **args, int fd);
extern int messages(client_t *client, char **args, int fd);
extern int use(client_t *client, char **args, int fd);
extern int user(client_t *client, char **args, int fd);
extern int create(client_t *client, char **args, int fd);
extern int users(client_t *client, char **args, int fd);
extern int info(client_t *client, char **args, int fd);
extern int list(client_t *client, char **args, int fd);
extern int subscribe(client_t *client, char **args, int fd);
extern int unsubscribe(client_t *client, char **args, int fd);
extern int subscribed(client_t *client, char **args, int fd);
extern int help(client_t *client, char **args, int fd);

extern int login_response(client_t *client, void *payload);
extern int logout_response(client_t *client, void *payload);
extern int send_response(client_t *client, void *payload);
extern int messages_response(client_t *client, void *payload);
extern int use_response(client_t *client, void *payload);
extern int user_response(client_t *client, void *payload);
extern int create_response(client_t *client, void *payload);
extern int users_response(client_t *client, void *payload);
extern int info_response(client_t *client, void *payload);
extern int list_response(client_t *client, void *payload);
extern int subscribe_response(client_t *client, void *payload);
extern int unsubscribe_response(client_t *client, void *payload);
extern int subscribed_response(client_t *client, void *payload);
extern int help_response(client_t *client, void *payload);

typedef struct commands_s {
    char *identifier;
    int (*func)(client_t *, char **, int);
} commands_t;

extern const commands_t commands[NB_CMD];

typedef struct responses_s {
    uint code;
    int (*func)(client_t *, void *);
} responses_t;

extern const responses_t responses[NB_CMD];

char *get_next_cmd(circular_buff_t *buff);

#endif /* COMMAND_H_ */
