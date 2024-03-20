/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/
#ifndef CIRCULAR_BUFF_Hh
    #define CIRCULAR_BUFF_Hh

    #include "inc.h"

    #define SIZE 1024

typedef struct circular_buff_s {
    uint id;
} circular_buff_t;

char read_circular_buff(circular_buff_t *buff);

#endif //CIRCULAR_BUFF_Hh
