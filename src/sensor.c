#include "sensor.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/irq.h"

sensor_t* sensor_en;
void on_adc_wrap() {
    // adc_clear_irq();
    //if ((uint8_t)4 == adc_fifo_get_level()){
    for (int i = 0; sensor_en->len;  i++){
        sensor_en->state_a[i] = adc_fifo_get();
    }
    //}
    adc_fifo_drain();
    // gpio_put(PICO_DEFAULT_LED_PIN, true);
}

void sensor_init(sensor_t* sensor_mas, sensor_mode_t mode){
    sensor_en = sensor_mas;
    
    sensor_mas->mode = mode;
    if (mode == DIGITAL_sensor){ 
        for (uint i = 0; i < sensor_mas->len; i++){
            gpio_init(sensor_mas->gpio[i]);
            gpio_set_dir(sensor_mas->gpio[i], GPIO_IN);
        }
    } else {
        adc_init();
        // adc_irq_set_enabled(true);
        adc_fifo_setup(
            true,
            false,
            (uint16_t)sensor_mas->len,
            false,
            false
        );

        irq_set_exclusive_handler(ADC_IRQ_FIFO, on_adc_wrap);
        irq_set_priority(ADC_IRQ_FIFO, 10);	
        irq_set_enabled(ADC_IRQ_FIFO, true);
        
        uint16_t temp;
        for (uint i = 0; i < sensor_mas->len; i++){
            adc_gpio_init(26 + i);
            temp |= (1 << i);
            // adc_select_input(0);

        }
        adc_set_round_robin(temp);
        adc_irq_set_enabled(true);
    }
}

void sensor_read(sensor_t* sensor_mas){
    if (sensor_mas->mode == DIGITAL_sensor){ 
        sensor_mas->state_d = 0;
        static bool temp;
        for (uint i = 0; i < sensor_mas->len; i++){
            temp = gpio_get(sensor_mas->gpio[i]);
            sensor_mas->state_d |= temp << i;
        }
    } else {
        
        // adc_run(true);
        for (uint i = 0; i < sensor_mas->len; i++){
            adc_select_input(i);
            sensor_mas->state_a[i] = adc_read();
        }

    }
    
}
// ADC0_IRQ_FIFO

