#include"console.h"

#define MAX_CMD_LEN 256
#define MAX_CMDS 32


typedef void (*func)(void);

typedef struct{
    char name[MAX_CMD_LEN];
    func callable;
} command_t;

static command_t cmd_list[MAX_CMDS];

void cmd_init(int baud_rate);
void cmd_add(char* name, func callable);
void cmd_help();
void cmd_monit();