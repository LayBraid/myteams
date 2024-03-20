/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "../include/include.h"
#include "../../shared/include/proto.h"
#include "../include/client.h"

void tester(client_t *test, raw_msg_t *cmd, int sock);
raw_msg_t handle_cmd(client_t *client, char *msg);

void assert_int(int a, int b);
void assert_str(char *a, char *b);

int main(int ac, char **av)
{
    // client that connect to a serv
    int sock = 0;
    struct sockaddr_in serv_addr;

    if (ac != 3) {
        printf("USAGE: ./client ip port\n");
        return (84);
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return (-1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(av[2]));
    if (inet_pton(AF_INET, av[1], &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return (-1);
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return (-1);
    }

    client_t *client = malloc(sizeof(client_t));
    client->socket = sock;
    client->state = PROCESS;
    client->data = NULL;
    client->uuid[0] = '\0';
    client->TEST = 0;


    tester(client, NULL, sock);
    fd_set readfds = {0};
    int maxfd = sock;
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(sock, &readfds);

        if (select(maxfd + 1, &readfds, NULL, NULL, NULL) == -1) {
            perror("select");
            return 84;
        }
        // recv from server
        if (FD_ISSET(sock, &readfds)) {
            void *wait = malloc(2048);
            ssize_t end = read(sock, wait, 2048);
            if (end == -1) {
                perror("read");
                return 84;
            }

            tester(client, (raw_msg_t *)wait, sock);
        }
    }
}

void tester(client_t *test, raw_msg_t *cmd, int sock)
{
    if (test->TEST == 0) {
        exe_cmd(test, strdup("/login \"isma\""), sock);
        test->TEST++;
    } else if (test->TEST == 1) {
        assert_int((int)cmd->code, LOGIN_RESPONSE);
    }
}

void assert_int(int a, int b)
{
    if (a != b) {
        printf("FAILED: %d != %d\n", a, b);
        exit(84);
    }

    // message valid assert
    printf("PASSED: %d == %d\n", a, b);
}

void assert_str(char *a, char *b)
{
    if (strcmp(a, b) != 0) {
        printf("FAILED: %s != %s\n", a, b);
        exit(84);
    }

    // message valid assert
    printf("PASSED: %s == %s\n", a, b);
}