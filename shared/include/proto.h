/*
** EPITECH PROJECT, 2023
** teams
** File description:
** ex00
*/


#ifndef TEAMS_PROTO_H
    #define TEAMS_PROTO_H

    #define UNMARSHALL(n) (s_##n##_t *)

    #define SERVER_LOGGER(n, ...) printf(n, ##__VA_ARGS__)

    #define CLIENT_LOGGER(fd, n, ...) dprintf(fd, n, ##__VA_ARGS__)

    #define SELF_LOGGER(n, ...) printf(n, ##__VA_ARGS__)

    #include "time.h"

typedef enum {
    LOGIN_REQUEST = 100,
    LOGIN_RESPONSE = 600,
    HELP_REQUEST = 101,
    HELP_RESPONSE = 601,
    LOGOUT_REQUEST = 102,
    LOGOUT_RESPONSE = 602,
    USERS_REQUEST = 103,
    USERS_RESPONSE = 603,
    USER_REQUEST = 104,
    USER_RESPONSE = 604,
    SEND_REQUEST = 105,
    SEND_RESPONSE = 605,
    MESSAGES_REQUEST = 106,
    MESSAGES_RESPONSE = 606,
    SUBSCRIBE_REQUEST = 107,
    SUBSCRIBE_RESPONSE = 607,
    SUBSCRIBED_REQUEST = 108,
    SUBSCRIBED_RESPONSE = 608,
    UNSUBSCRIBE_REQUEST = 109,
    UNSUBSCRIBE_RESPONSE = 609,
    USE_REQUEST = 110,
    USE_RESPONSE = 610,
    CREATE_REQUEST = 111,
    CREATE_RESPONSE = 611,
    LIST_REQUEST = 112,
    LIST_RESPONSE = 612,
    INFO_REQUEST = 113,
    INFO_RESPONSE = 613,
} request_code;

typedef enum {
    REQUEST_OK = 200,
    REQUEST_KO = 400,
    REQEST_UNAUTHORIZED = 401,
    REQUEST_FORBIDDEN = 403,
    REQUEST_UNKNOW = 404,
} request_status;

typedef enum {
    NO_ERROR = 700,
    ALREADY_CONNECTED = 701,
    NOT_CONNECTED = 702,
    ALREADY_EXIST = 703,
    NOT_FOUND = 704,
} error_code;

typedef enum {
    CONTEXT_NONE = 0,
    CONTEXT_TEAM = 1,
    CONTEXT_CHANNEL = 2,
    CONTEXT_THREAD = 3,
} use_context;

typedef enum {
    LOGOUT,
    CONNECTED,
} user_status;

typedef unsigned int uint;

typedef struct raw_msg_s {
    uint code;
} raw_msg_t;

typedef struct help_request_s {
    uint code;
    char cmd[25];
} s_help_request_t; // help

typedef struct help_response_s {
    uint code;
    char *cmd;
    char *desc;
    request_status status_code;
    error_code error_code;
} s_help_response_t; // help

typedef struct login_request_s {
    uint code;
    char username[32];
    char uuid[37];
} s_login_request_t; // login

typedef struct login_response_s {
    uint code;
    char username[32];
    char uuid[37];
    request_status status_code;
    error_code error_code;
} s_login_response_t; // login

typedef struct logout_request_s {
    uint code;
    char uuid[37];
} s_logout_request_t; // logout

typedef struct logout_response_s {
    uint code;
    char uuid[37];
    char username[32];
    request_status status_code;
    error_code error_code;
} s_logout_response_t; // logout

typedef struct users_request_s {
    uint code;
} s_users_request_t; // users

typedef struct users_response_s {
    uint code;
    char uuid[37];
    char username[32];
    request_status status_code;
    error_code error_code;
} s_users_response_t; // users

typedef struct user_request_s {
    uint code;
    char uuid[37];
} s_user_request_t; // user

typedef struct user_response_s {
    uint code;
    char username[32];
    char uuid[37];
    request_status status_code;
    error_code error_code;
} s_user_response_t; // user

typedef struct send_request_s {
    uint code;
    char uuid_sender[37];
    char uuid_receiver[37];
    time_t timestamp;
    char msg[1024];
} s_send_request_t; // send

typedef struct send_response_s {
    uint code;
    char uuid_sender[37];
    char uuid_receiver[37];
    char msg[1024];
    time_t timestamp;
    request_status status_code;
    error_code error_code;
} s_send_response_t; // send

typedef struct subscribe_request_s {
    uint code;
    char uuid_user[37];
    char uuid_team[37];
} s_subscribe_request_t; // subscribe

typedef struct subscribe_response_s {
    uint code;
    char uuid_user[37];
    char uuid_team[37];
    request_status status_code;
    error_code error_code;
} s_subscribe_response_t; // subscribe

typedef struct unsub_request_s {
    uint code;
    char uuid_user[37];
    char uuid_team[37];
} s_unsub_request_t; // unsubscribe

typedef struct unsub_response_s {
    uint code;
    char uuid_user[37];
    char uuid_team[37];
    request_status status_code;
    error_code error_code;
} s_unsub_response_t; // unsubscribe

typedef struct messages_request_s {
    uint code;
    char uuid_sender[37];
    char uuid_subject[37];
    time_t timestamp;
} s_messages_request_t; // messages

typedef struct messages_response_s {
    uint code;
    char uuid_sender[37];
    char uuid_receiver[37];
    char msg[1024];
    time_t timestamp;
    request_status status_code;
    error_code error_code;
} s_messages_response_t; // messages

typedef struct subscribed_request_s {
    uint code;
    char uuid[37];
    char team_uuid[37];
} s_subscribed_request_t; // subscribed

typedef struct subscribed_response_s {
    uint code;
    char uuid[37];
    char name[32];
    char description[255];
    request_status status_code;
    error_code error_code;
    int logged;
} s_subscribed_response_t; // subscribed

typedef struct use_request_s {
    uint code;
    char uuid[37];
    char team_uuid[37];
    char channel_uuid[37];
    char thread_uuid[37];
} s_use_request_t; // use

typedef struct use_response_s {
    uint code;
    char uuid[37];
    char team_uuid[37];
    char channel_uuid[37];
    char thread_uuid[37];
    use_context context;
    request_status status_code;
    error_code error_code;
} s_use_response_t; // use

typedef struct create_request_s {
    uint code;
    char uuid[37];
    char team_uuid[37];
    char channel_uuid[37];
    char thread_uuid[37];
    char first_arg[512];
    char second_arg[512];
    time_t timestamp;
} s_create_request_t; // create

typedef struct create_response_s {
    uint code;
    use_context context;
    char uuid[37];
    char team_uuid[37];
    char channel_uuid[37];
    char thread_uuid[37];
    char name[32];
    char description[255];
    char body[512];
    time_t timestamp;
    request_status status_code;
    error_code error_code;
} s_create_response_t; // create

typedef struct info_request_s {
    uint code;
    char uuid[37];
} s_info_request_t; // info

typedef struct info_response_s {
    uint code;
    use_context context;
    user_status user_status;
    char uuid[37];
    char team_uuid[37];
    char channel_uuid[37];
    char thread_uuid[37];
    char name[32];
    char description[255];
    char body[512];
    time_t timestamp;
    request_status status_code;
    error_code error_code;
} s_info_response_t; // info

typedef struct list_request_s {
    uint code;
    char uuid[37];
} s_list_request_t; // list

typedef struct list_response_s {
    uint code;
    use_context context;
    char uuid[37];
    char team_uuid[37];
    char channel_uuid[37];
    char thread_uuid[37];
    char name[32];
    char description[255];
    char body[512];
    time_t timestamp;
    request_status status_code;
    error_code error_code;
} s_list_response_t; // list

#endif //TEAMS_PROTO_H
