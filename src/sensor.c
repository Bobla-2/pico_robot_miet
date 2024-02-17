#include "sensor.h"
#include "pico/stdlib.h"

void sensor_init(sensor_t* sensor_mas){
    for (uint i = 0; i < sensor_mas->len; i++){
        gpio_init(sensor_mas->gpio[i]);
        gpio_set_dir(sensor_mas->gpio[i], GPIO_IN);
    }
}

void sensor_read(sensor_t* sensor_mas){
    sensor_mas->state = 0;
    static bool temp;
    for (uint i = 0; i < sensor_mas->len; i++){
        temp = gpio_get(sensor_mas->gpio[i]);
        sensor_mas->state |= temp << i;
    }
}


