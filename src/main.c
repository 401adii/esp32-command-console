#include"cmd_manager.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"

#define BAUD_RATE 115200

void app_main() {
    cmd_init(BAUD_RATE);
    while(1){
        cmd_monit();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}