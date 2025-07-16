#include<string.h>
#include<ctype.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"driver/uart.h"

#define MAX_LENGTH 256
#define CONSOLE UART_NUM_0
#define BUFFER_SIZE 1024 * 2

void console_init(int baud_rate);
void console_print(char* msg);
int console_available();
void console_readln(char* buff);