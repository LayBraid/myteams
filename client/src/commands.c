/*
** EPITECH PROJECT, 2023
** playground
** File description:
** No file there , just an epitech header example
*/

#include "command.h"

const commands_t commands[NB_CMD] = {
        {"/login", login},
        {"/logout", logout},
        {"/send", send_command},
        {"/messages", messages},
        {"/use", use},
        {"/user", user},
        {"/create", create},
        {"/users", users},
        {"/info", info},
        {"/list", list},
        {"/subscribe", subscribe},
        {"/unsubscribe", unsubscribe},
        {"/subscribed", subscribed},
        {"/help", help},
};

const responses_t responses[NB_CMD] = {
        {LOGIN_RESPONSE, login_response},
        {LOGOUT_RESPONSE, logout_response},
        {SEND_RESPONSE, send_response},
        {USER_RESPONSE, user_response},
        {USE_RESPONSE, use_response},
        {CREATE_RESPONSE, create_response},
        {LIST_RESPONSE, list_response},
        {USERS_RESPONSE, users_response},
        {INFO_RESPONSE, info_response},
        {MESSAGES_RESPONSE, messages_response},
        {SUBSCRIBE_RESPONSE, subscribe_response},
        {UNSUBSCRIBE_RESPONSE, unsubscribe_response},
        {SUBSCRIBED_RESPONSE, subscribed_response},
        {HELP_RESPONSE, help_response},
};

void remove_trailing(char *str)
{
    if (*str == '\0')
        return;
    if (*str == '\r' || *str == '\n')
        *str = '\0';
    remove_trailing(str + 1);
}
