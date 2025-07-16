#include"driver/gpio.h"
#include"cmd_manager.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"

#define BAUD_RATE 115200

static uint8_t state = 0;

void gpio_init(void){
    gpio_config_t config = {
        .pin_bit_mask = 1 << GPIO_NUM_2,
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&config);
}

void switch_led(void){
    state = !state;
    gpio_set_level(GPIO_NUM_2, state);
}

void app_main() {
    gpio_init();
    cmd_init(BAUD_RATE);
    cmd_add("led\n", switch_led);
    while(1){
        cmd_monit();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}