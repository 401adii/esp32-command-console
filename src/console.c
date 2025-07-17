#include"console.h"

void console_init(int baud_rate){
    uart_config_t config = {
        .baud_rate = baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .stop_bits = UART_STOP_BITS_1,
        .parity = UART_PARITY_DISABLE,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_param_config(CONSOLE, &config);
    uart_driver_install(CONSOLE, BUFFER_SIZE, BUFFER_SIZE, 0, NULL, 0);
}

void console_print(char *msg){
    uart_write_bytes(CONSOLE, msg, strlen(msg) * sizeof(char));
}

int console_available(){
    size_t len;
    uart_get_buffered_data_len(CONSOLE, &len);
    return len > 0 ? len : 0;
}

void console_readln(char* buff){
    int index = 0;
    int line_end = 0;
    char c;
    while(index < MAX_LENGTH - 1 && !line_end){
        if(uart_read_bytes(CONSOLE, &c, 1, portMAX_DELAY) == 1){
            switch(c){
            case '\n':
            case '\r':
                line_end = 1;
                break;
            case '\b':
            case 0x7f:
                if(index > 0)
                    index--;
                break;
            default:
                if(isprint(c)){
                    buff[index++] = c;
                }
            break;
            }
        }
    }
    buff[index] = '\0';
    console_print(buff);
    console_print("\n");
}