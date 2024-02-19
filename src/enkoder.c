// #include <stdint.h>
#include "enkoder.h"
// #include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

enkoder_t* enkoder_mas[2];

void gpio_callback(uint gpio, uint32_t events){
    if(enkoder_mas[0]->gpio == gpio) enkoder_mas[0]->count += 1;
    if(enkoder_mas[1]->gpio == gpio) enkoder_mas[1]->count += 1;
    
    
}
void enkoder_init(enkoder_t* enkoder_L, enkoder_t* enkoder_R){
    gpio_set_irq_enabled_with_callback(enkoder_L->gpio, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(enkoder_R->gpio, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    enkoder_mas[0] = enkoder_L;
    enkoder_mas[1] = enkoder_R;
}



// void enkoder_read(enkoder_t* enkoder){
//     static bool temp_state;
//     temp_state = gpio_get(enkoder->gpio);
//     if (temp_state && !enkoder->state){
//         enkoder->state = true;
//         enkoder->count += 1;
//     } else if (!temp_state && enkoder->state){
//         enkoder->state = false;
//     }
// } 

