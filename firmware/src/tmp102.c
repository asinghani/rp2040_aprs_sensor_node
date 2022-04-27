#include <pico/stdlib.h>
#include "hardware/i2c.h"

#define TMP102_SDA 8
#define TMP102_SCL 1

#define TMP102_I2C_FREQ 1

// Set up the I2C interface
void tmp102_init() {
    i2c_init(i2c0, TMP102_I2C_FREQ);
    gpio_set_function(TMP102_SDA, GPIO_FUNC_I2C);
    gpio_set_function(TMP102_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(TMP102_SDA);
    gpio_pull_up(TMP102_SCL);
}

// Read the temperature in degrees F
float tmp102_read_temperature() {
    uint8_t buf[2];
    i2c_read_blocking(i2c0, 0x48, (void*)&buf, 2, false);
    int16_t reg = ((int16_t)buf[0]) << 8 | ((int16_t)buf[1]);
    reg >>= 4;
    float temp = reg*0.1125 + 32;
    return temp;
}
