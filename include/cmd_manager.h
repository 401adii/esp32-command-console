#ifndef CMD_MANAGER_H
#define CMD_MANAGER_H

#include"console.h"

#define MAX_CMDS 32
#define MAX_CMD_NAME_LEN 32
#define MAX_CMD_DESC_LEN 128


typedef void (*func)(void);

typedef struct{
    char name[MAX_CMD_NAME_LEN];
    func callable;
    char description[MAX_CMD_DESC_LEN];
} command_t;

extern command_t cmd_list[MAX_CMDS];

void cmd_init(int baud_rate);
void cmd_add(command_t *command);
void cmd_help();
void cmd_monit();

#endif