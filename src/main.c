#include"console.h"

#define BAUD_RATE 115200

void app_main() {
    console_init(BAUD_RATE);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    console_print("\n\nConsole initialized! Type \'h\' for help\n");
    while(1){
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}