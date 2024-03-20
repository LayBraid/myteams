/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/
#ifndef CLIENT_H_
    #define CLIENT_H_

    #include "inc.h"
    #include "socket.h"
    #include "proto_buff.h"

typedef struct client_s client_t;
struct client_s {
    client_t *next;
    char username[32];
    char uuid[37];
    socket_t socket;
    void *rec;
    void *send;
    bool logged;
    enum status {
        NONE,
        DISCONNECTED,
    } status;
    char context_team[37];
    char context_channel[37];
    char context_thread[37];
    data_socket_t *data_socket;
};

    #define FOR_EACH(server, list, func, ...) { \
    client_t *tmp = *list; \
    while (tmp) { \
        client_t *next = tmp->next;\
        int i = func(tmp __VA_OPT__(,) __VA_ARGS__); \
        if (i == 1) \
            delete_client(server, tmp, list, 0); \
        tmp = next; \
    } \
}

    #define FOR_EACH_SRV(list, serv, func, ...) { \
    client_t *tmp = *list; \
    while (tmp) { \
        client_t *next = tmp->next;\
        int i = func(serv, tmp __VA_OPT__(,) __VA_ARGS__); \
        if (i == 1) \
            delete_client(serv, tmp, list, 0); \
        tmp = next; \
    } \
}

int handle_req(client_t *list, char *rec);

/* ### CIRCULAR_BUFF ### */
circular_buff_t *new_circular_buff(void);
void free_circular_buff(circular_buff_t *buff);
char *get_next_cmd(circular_buff_t *buff);
char dec_read_circle_buff(circular_buff_t *buff);

void delete_data_socket(data_socket_t *data_sock);

#endif //CLIENT_H_
