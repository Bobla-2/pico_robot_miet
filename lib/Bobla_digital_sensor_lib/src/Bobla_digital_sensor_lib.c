#include "Bobla_digital_sensor_lib.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

bobla_digital_sensor_t* digital_sensor_en;


void digital_sensor_init(bobla_digital_sensor_t* digital_sensor){

    //digital_sensor_en = digital_sensor;
    for (uint i = 0; i < digital_sensor->len_gpio; i++){
        gpio_init(digital_sensor->gpio[i]);
        gpio_set_dir(digital_sensor->gpio[i], GPIO_IN);
    }    
}

void digital_sensor_read(bobla_digital_sensor_t* digital_sensor){
    digital_sensor->state = 0;
    static bool temp = 0;
    for (uint i = 0; i < digital_sensor->len_gpio; i++){
        temp = gpio_get(digital_sensor->gpio[i]);
        if (digital_sensor->inversion == true){
            digital_sensor->state |= !temp << i;
        } else{
            digital_sensor->state |= temp << i;
        }
        
    }   
    if (digital_sensor->state == 0){}
}


