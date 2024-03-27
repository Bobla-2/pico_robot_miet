#include "Bobla_brawls_sensor_lib.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

bobla_brawls_sensor_t* brawls_sensor_en;


void brawls_sensor_init(bobla_brawls_sensor_t* brawls_sensor){
    brawls_sensor_en = brawls_sensor;
    for (uint i = 0; i < brawls_sensor_en->len_gpio; i++){
        gpio_init(brawls_sensor_en->gpio[i]);
        gpio_set_dir(brawls_sensor_en->gpio[i], GPIO_IN);
    }    
}

void brawls_sensor_read(){
    brawls_sensor_en->state = 0;
    static bool temp = 0;
    for (uint i = 0; i < brawls_sensor_en->len_gpio; i++){
        temp = gpio_get(brawls_sensor_en->gpio[i]);
        brawls_sensor_en->state |= temp << i;
    }   
    if (brawls_sensor_en->state == 0){}
}


