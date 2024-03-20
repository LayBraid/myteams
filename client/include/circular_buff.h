/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/
#ifndef CIRCULAR_BUFF_Hh
    #define CIRCULAR_BUFF_Hh

    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdbool.h>

    #define SIZE 2048

typedef struct circular_buff_s {
    char *buffer;
    char *read_head;
    char *write_head;
} circular_buff_t;

char read_circular_buff(circular_buff_t *buff);

#endif //CIRCULAR_BUFF_Hh
