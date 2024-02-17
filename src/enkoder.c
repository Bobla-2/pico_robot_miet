
#include "enkoder.h"

void enkoder_init(enkoder_t* enkoder){
    gpio_init(enkoder->gpio);
    gpio_set_dir(enkoder->gpio, GPIO_IN);
}

void enkoder_read(enkoder_t* enkoder){
    static bool temp_state;
    temp_state = gpio_get(enkoder->gpio);
    if (temp_state && !enkoder->state){
        enkoder->state = true;
        enkoder->count += 1;
    } else if (!temp_state && enkoder->state){
        enkoder->state = false;
    }
} 

