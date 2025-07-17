#include"string.h"
#include"driver/gpio.h"
#include"cmd_manager.h"
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"

#define BAUD_RATE 115200

void command_config(void);
void gpio_set_to_output(void *param);
void gpio_set_high(void *param);
void gpio_set_low(void *param);

void app_main(void) {
    cmd_init(BAUD_RATE);
    command_config();
    while(1){
        cmd_monit();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void command_config(void){
    command_t gpio_command = {
        .name = "gpio_set",
        .description = "Sets GPIO to OUTPUT mode, takes PIN number as an argument",
        .callable = gpio_set_to_output, 
    };
    command_t enable_command = {
        .name = "gpio_enable",
        .description = "Sets GPIO state to HIGH, takes PIN number as an argument",
        .callable =  gpio_set_high,
    };
    command_t disable_command = {
        .name = "gpio_disable",
        .description = "Sets GPIO state to LOW, takes PIN number as an argument",
        .callable = gpio_set_low,
    };

    cmd_add(&gpio_command);
    cmd_add(&enable_command);
    cmd_add(&disable_command);
}


void gpio_set_to_output(void *param){
    int pin;
    pin = atoi((char*)param);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
}

void gpio_set_high(void *param){
    int pin;
    pin = atoi((char*)param);
    gpio_set_level(pin, 1);
}

void gpio_set_low(void *param){
    int pin;
    pin = atoi((char*)param);
    gpio_set_level(pin, 0);
}
