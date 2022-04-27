#include "dra818.h"
#include <pico/stdlib.h>

void dra818_init_aprs() {
    // Set up the radio control signals
    gpio_set_function(DRA_PTT, GPIO_FUNC_SIO);
    gpio_set_function(DRA_PD, GPIO_FUNC_SIO);
    gpio_set_function(DRA_PWR, GPIO_FUNC_SIO);

    gpio_set_dir(DRA_PTT, true);
    gpio_set_dir(DRA_PD, true);
    gpio_set_dir(DRA_PWR, true);
    gpio_put(DRA_PTT, true);
    gpio_put(DRA_PD, true);
    gpio_put(DRA_PWR, false);

    // Initialize UART
    gpio_set_function(DRA_RX, GPIO_FUNC_UART);
    gpio_set_function(DRA_TX, GPIO_FUNC_UART);
    uart_init(uart1, 9600);
    sleep_ms(100);
    uart_set_translate_crlf(uart1, false);
    uart_puts(uart1, "\r\n");
    uart_puts(uart1, "\r\n");
    sleep_ms(200);
    // Set the APRS frequency and no CTCSS
    uart_puts(uart1, "AT+DMOSETGROUP=0,144.3900,144.3900,0000,1,0000\r\n");
    sleep_ms(200);

    printf("\ndone init\n");
}

void dra818_set_lowpower(bool low_power) {
    if (low_power) {
        // Low
        gpio_set_dir(DRA_PWR, true);
        gpio_put(DRA_PWR, false);
    } else {
        // Float
        gpio_set_dir(DRA_PWR, false);
    }
}

void dra818_key(bool transmit) {
    gpio_put(DRA_PTT, !transmit);
}
