/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/
#ifndef REQUEST_H_
    #define REQUEST_H_

    #include "inc.h"
    #include <string.h>
    #include <stdlib.h>
    #include "client.h"
    #include "command.h"
    #include "../../shared/include/proto.h"

int occurence(char *str, char c);
void remove_trailing(char *str);
void free_tab(char **tab);

#endif //REQUEST_H_
