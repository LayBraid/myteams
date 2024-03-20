/*
** EPITECH PROJECT, 2023
** ftp
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

const commands_t commands[NB_CMD] = {
        {LOGIN_REQUEST,  "LOGIN", login},
        {LOGOUT_REQUEST, "LOGOUT", logout},
        {HELP_REQUEST,   "HELP", help},
        {USERS_REQUEST,  "USERS", users},
        {USER_REQUEST,   "USER", user},
        {USE_REQUEST,    "USE", use},
        {CREATE_REQUEST, "CREATE", create},
        {SEND_REQUEST, "SEND", send_command},
        {MESSAGES_REQUEST, "MESSAGES",messages},
        {SUBSCRIBE_REQUEST, "SUBSCRIBE", subscribe},
        {UNSUBSCRIBE_REQUEST, "UNSUBSCRIBE", unsubscribe},
        {SUBSCRIBED_REQUEST, "SUBSCRIBED", subscribed},
        {LIST_REQUEST, "LIST", list},
        {INFO_REQUEST, "INFO", info}
};
