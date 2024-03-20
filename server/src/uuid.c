/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#include "my_uuid.h"

char *generate_uuid(void)
{
    char *uuid = malloc(sizeof(char) * 37);

    for (int i = 0; i < 36; i++)
        if (i == 8 || i == 13 || i == 18 || i == 23)
            uuid[i] = '-';
        else
            uuid[i] = (rand() % 10) + 48;
    uuid[36] = '\0';
    return uuid;
}
