#include"cmd_manager.h"

command_t cmd_list[MAX_CMDS];

void cmd_init(int baud_rate){
    console_init(baud_rate);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    for(int i = 0; i < MAX_CMDS; i++)
    memset(cmd_list[i].name, '\0', MAX_CMD_LEN);
    cmd_add("help\n", cmd_help);
    console_print("\n\nConsole initialized! Enter 'help' for more info.\n");
}

void cmd_add(char *name, func callable){
    int idx = -1;
    for(int i = 0; i < MAX_CMDS; i++){
        if(cmd_list[i].name[0] == '\0'){
            idx = i;
            break;
        }
    }
    if(idx == -1)
        return;
    
    strncpy(cmd_list[idx].name, name, MAX_CMD_LEN - 1);
    cmd_list[idx].name[MAX_CMD_LEN - 1] = '\0';
    cmd_list[idx].callable = callable;
}

void cmd_help(){
    console_print("\nThis is console command interface that allows adding custom commands and calling functions via serial monitor\n");
    console_print("List of available commands:\n");
    for(int i = 0; i < MAX_CMDS; i++){
        if(cmd_list[i].name[0] == '\0')
            break;
        console_print(cmd_list[i].name);
    }
}

void cmd_monit(){
    if(console_available() < 0)
        return;
    char buff[MAX_CMD_LEN];
    console_readln(buff);
    console_print(buff);

    int found = 0;
    for(int i = 0; i < MAX_CMDS && cmd_list[i].name[0] != '\0'; i++){
        if(strcmp(buff, cmd_list[i].name) == 0){
            found = 1;
            cmd_list[i].callable();
            break;
        }
    }
    if(!found)
        console_print("Error: command not found\n");
}