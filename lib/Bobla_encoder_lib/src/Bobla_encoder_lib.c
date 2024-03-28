#include "Bobla_encoder_lib.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"
// #include "hardware/time.h"

enkoder_t* enkoder_mas[2];

void gpio_callback(uint gpio, uint32_t events){
    if(enkoder_mas[0]->gpio == gpio) enkoder_mas[0]->count += 1;
    if(enkoder_mas[1]->gpio == gpio) enkoder_mas[1]->count += 1;
    
    
}
void enkoder_init_with_irq(enkoder_t* enkoder_L, enkoder_t* enkoder_R){
    gpio_set_irq_enabled_with_callback(enkoder_L->gpio, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(enkoder_R->gpio, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    enkoder_mas[0] = enkoder_L;
    enkoder_mas[1] = enkoder_R;
}

void enkoder_init_NO_irq(enkoder_t* enkoder_L, enkoder_t* enkoder_R){
    gpio_init(enkoder_L->gpio);
    gpio_init(enkoder_R->gpio);
    gpio_set_dir(enkoder_R->gpio, false);
    gpio_set_dir(enkoder_L->gpio, false);
    gpio_pull_down(enkoder_R->gpio);
    gpio_pull_down(enkoder_L->gpio);
    enkoder_mas[0] = enkoder_L;
    enkoder_mas[1] = enkoder_R;
}

void set_rpm(int num_encoder){
    if  (time_us_32() - enkoder_mas[num_encoder]->time_old_stamp > 200000){ //5Hz
        enkoder_mas[num_encoder]->rmp = enkoder_mas[num_encoder]->count - enkoder_mas[num_encoder]->old_count;
        enkoder_mas[num_encoder]->old_count = enkoder_mas[num_encoder]->count;
        enkoder_mas[num_encoder]->time_old_stamp = time_us_32();
    }
}

void enkoder_core_no_irq(){
    static bool temp_state;
    for(int i = 0; i < 2; i++){
        temp_state = gpio_get(enkoder_mas[i]->gpio);
        if (temp_state && !enkoder_mas[i]->state){
            enkoder_mas[i]->state = true;
            enkoder_mas[i]->count += 1;
            set_rpm(i);
        } else if (!temp_state && enkoder_mas[i]->state){
            enkoder_mas[i]->state = false;
            enkoder_mas[i]->count += 1;
        }
    }
} 

