#include "sensor.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/irq.h"

sensor_t* sensor_en;

irq_handler_t  on_adc_wrap(void) {
    for (size_t i = 0; i < sensor_en->len;  i++){
        sensor_en->state_a[i] = adc_fifo_get();
    }
    adc_fifo_drain();
}

void sensor_init(sensor_t* sensor_mas){
    sensor_en = sensor_mas;
    
    
    if (sensor_mas->mode == DIGITAL_sensor){ 
        for (uint i = 0; i < sensor_mas->len; i++){
            gpio_init(sensor_mas->gpio[i]);
            gpio_set_dir(sensor_mas->gpio[i], GPIO_IN);
        }
    } else {
        adc_init();
        
        uint16_t temp;
        for (uint i = 0; i < sensor_mas->len; i++){
            adc_gpio_init(26 + i);
            temp |= (1 << i);
        }
            
        adc_fifo_setup(
            true,
            false,
            sensor_mas->len,
            false,
            true
        );
        if (irq_has_shared_handler(ADC_IRQ_FIFO)){
           irq_add_shared_handler(ADC_IRQ_FIFO, on_adc_wrap, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY );
        }else{
            irq_set_exclusive_handler(ADC_IRQ_FIFO, on_adc_wrap);
        }
        irq_set_priority (ADC_IRQ_FIFO, PICO_HIGHEST_IRQ_PRIORITY);
        irq_set_enabled(ADC_IRQ_FIFO, true);
        adc_set_round_robin(temp);
        adc_irq_set_enabled(true);
        adc_set_clkdiv(1000);
        adc_fifo_drain();
        adc_run(true);
    }
       
    printf("\r\nXUI!");
    
}

void sensor_read_digital(){
    if (sensor_en->mode == DIGITAL_sensor){ 
        sensor_en->state_d = 0;
        static bool temp;
        for (uint i = 0; i < sensor_en->len; i++){
            temp = gpio_get(sensor_en->gpio[i]);
            sensor_en->state_d |= temp << i;
        }
    }    
}


