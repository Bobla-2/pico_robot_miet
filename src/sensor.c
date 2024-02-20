#include "sensor.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/irq.h"

sensor_t* sensor_en;

volatile bool flag = false;

irq_handler_t  on_adc_wrap(void) {
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    static uint16_t i = 0;
    flag = true;
    //printf("123");
    
    // //if ((uint8_t)4 == adc_fifo_get_level()){
    // for (int i = 0; sensor_en->len - 1;  i++){
        // sensor_en->state_a[0] = adc_fifo_get();

    //adc_fifo_drain();
    sensor_en->state_a[0] = adc_fifo_get();
    while (!adc_fifo_is_empty())
        (void) adc_fifo_get();
    //printf("H");
    //adc_irq_set_enabled (false);
    //printf("H");
    //printf("H");
    //irq_clear (ADC_IRQ_FIFO);
    
    //irq_set_enabled(ADC_IRQ_FIFO, false);
    //irq_set_enabled(ADC_IRQ_FIFO, true);
    //printf("H");
         //printf("");
    // }
    // //}
    //adc_fifo_drain();
    // adc_run(false);

}

void sensor_init(sensor_t* sensor_mas){
    sensor_en = sensor_mas;
    
    // sensor_mas->mode = mode;
    // if (mode == DIGITAL_sensor){ 
    //     for (uint i = 0; i < sensor_mas->len; i++){
    //         gpio_init(sensor_mas->gpio[i]);
    //         gpio_set_dir(sensor_mas->gpio[i], GPIO_IN);
    //     }
    // } else {
        adc_init();
        // adc_irq_set_enabled(true);
        
        // uint16_t temp;
        //for (uint i = 0; i < sensor_mas->len; i++){
            adc_gpio_init(26);// + i);
            adc_select_input(0);
            // temp |= (1 << i);
            // temp = 7;
            // adc_select_input(0);

        //}
        
        adc_fifo_setup(
            true,
            false,
            4,
            //(uint16_t)sensor_mas->len - 1,
            false,
            true
        );
        //if (irq_has_shared_handler(ADC_IRQ_FIFO)){
        //    irq_add_shared_handler(ADC_IRQ_FIFO,on_adc_wrap, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY );
        //}else{
            irq_set_exclusive_handler(ADC_IRQ_FIFO, on_adc_wrap);
        //}
        irq_set_priority (ADC_IRQ_FIFO, PICO_HIGHEST_IRQ_PRIORITY);
        // // irq_set_priority(ADC_IRQ_FIFO, PICO_DEF);	
        irq_set_enabled(ADC_IRQ_FIFO, true);
        // // adc_set_round_robin(temp);
        
        // gpio_put(PICO_DEFAULT_LED_PIN, true);
        adc_irq_set_enabled(true);
        adc_set_clkdiv(10000);
        adc_fifo_drain();
        printf("!");
        adc_run(true);
        //adc_fifo_get_blocking();
        
        while (flag == false)
        {
            printf("=");
            sleep_ms(100);
            /* code */
        }
        printf("\r\nXUI!");
    // }
}

void sensor_read(sensor_t* sensor_mas){
    // if (sensor_mas->mode == DIGITAL_sensor){ 
    //     sensor_mas->state_d = 0;
    //     static bool temp;
    //     for (uint i = 0; i < sensor_mas->len; i++){
    //         temp = gpio_get(sensor_mas->gpio[i]);
    //         sensor_mas->state_d |= temp << i;
    //     }
    // } else {
        
    //     adc_run(true);
    //     // for (uint i = 0; i < sensor_mas->len; i++){
    //     //     adc_select_input(i);
    //     //     sensor_mas->state_a[i] = adc_read();
    //     // }

    // }
    const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
        sleep_ms(500);
    
}
// ADC0_IRQ_FIFO

