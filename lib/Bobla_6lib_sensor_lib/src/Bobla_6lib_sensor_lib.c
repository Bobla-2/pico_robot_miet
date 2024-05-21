#include "Bobla_6lib_sensor_lib.h"
#include "hardware/timer.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/time.h"




// void l6_sensor_init(bobla_6lib_sensor_t* digital_sensor){

//     for (uint i = 0; i < digital_sensor->len_gpio; i++){
//         gpio_init(digital_sensor->gpio[i]);
//         gpio_set_dir(digital_sensor->gpio[i], GPIO_IN);
//     }    
// }

// void l6_sensor_read(){
//     digital_sensor->state = 0;
//     static bool temp = 0;
//     for (uint i = 0; i < digital_sensor->len_gpio; i++){
//         temp = gpio_get(digital_sensor->gpio[i]);
//         if (digital_sensor->inversion == true){
//             digital_sensor->state |= !temp << i;
//         } else{
//             digital_sensor->state |= temp << i;
//         }
        
//     }   
//     if (digital_sensor->state == 0){}
// }


bobla_6lib_sensor_t* en_s;

void gpio_callback2(uint gpio, uint32_t events){
    if (gpio == en_s->gpio_echo) {
        if (events == GPIO_IRQ_EDGE_RISE){
            en_s->old_time_stamp = time_us_32();
            // en_s->time_stamp += 1;
        } else if (events == GPIO_IRQ_EDGE_FALL){
            en_s->len = (time_us_32() - en_s->old_time_stamp)/58;
            en_s->old_time_stamp = 0;
        }
    }
}

void l6_sensor_init(bobla_6lib_sensor_t* sensor){
    en_s = sensor;
    gpio_set_irq_enabled_with_callback(en_s->gpio_echo, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback2);
    gpio_init(en_s->gpio_trig);
    gpio_set_dir(en_s->gpio_trig, GPIO_OUT);
}

void l6_sensor_read(){
    gpio_put(en_s->gpio_trig, 1);
    sleep_us(10);
    gpio_put(en_s->gpio_trig, 0);
}

