#include"cmd_manager.h"

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
    for(int i = 0; i < strlen(name); i++){
        cmd_list[idx].name[i] = name[i];
    }
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

    for(int i = 0; i < MAX_CMDS; i++){
        if(cmd_list[i].name[0] == '\0')
            break;

        if(strcmp(buff, cmd_list[i].name) == 0){
            cmd_list[i].callable();
            memset(buff, '\0', MAX_CMD_LEN);
        }
        else{
            console_print("Error: command not found\n");
        }
    }
}