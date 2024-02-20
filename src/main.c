#include "sensor.h"
// #include "motor_dc_pwm.h"
#include "motor_robot.h"
#include "enkoder.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
// #include <stdio.h>

uint temp_gpio[] = {26,27,28};
uint16_t temp_data_analog[3];
sensor_t sensor = {
    .gpio = temp_gpio,
    .len = 3,
    .mode = ANALOG_sensor,
    .state_a = temp_data_analog,

};
// motor_dc_pwm_t motor_dc_L = {
//     .gpioA = 2,
//     .gpioB = 3,
//     .speed = 0,
// };
// motor_dc_pwm_t motor_dc_R = {
//     .gpioA = 4,
//     .gpioB = 5,
//     .speed = 0,
// };
// motor_robot_t motor_robot = {
//     .motor_L = &motor_dc_L,
//     .motor_R = &motor_dc_R,
// };

motor_dc_pwm_6612_t  motor_robot_6612 = {
    .gpio_Lin1 = 8, //8     a=l
    .gpio_Lin2 = 9, //9        b=r
    .gpio_Rin1 = 7,  //7
    .gpio_Rin2 = 6,  //6
    .gpio_Lpwm = 10,
    .gpio_Rpwm = 11,
    .gpio_stby = 12, 
    .k2_R = 1,    
};

enkoder_t enkoder_L = {
    .gpio = 19,
};
enkoder_t enkoder_R = {
    .gpio = 18,
};

void main_init(){
    stdio_init_all();
    //enkoder_init(&enkoder_L, &enkoder_R);
    
    
    //motor_6612_robot_init(&motor_robot_6612);
    
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    sensor_init(&sensor);
}

int main() {
    
    main_init();
    int engle_temp = 180;
    //  stdio_init_all();
    gpio_put(PICO_DEFAULT_LED_PIN, false);
    //adc_init();
 
    // Make sure GPIO is high-impedance, no pullups etc
    //adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    //adc_select_input(0);
    while (true) {
        // sensor_read(&sensor);

        // static uint32_t time_stamp;
        // static uint32_t time_old_stamp;

        // // static uint32_t temp;
        // // static char temp_str[128];
        // time_stamp = time_us_32(); //  125.000 ≈ 1mc
        // if  (time_stamp - time_old_stamp > 5000){
            
        //     // if  (temp == 1){
        //         // temp = 0;
        //         gpio_put(PICO_DEFAULT_LED_PIN, true);
        //         // motor_6612_robot_forward_turn_encoder(&motor_robot_6612, &enkoder_R, &enkoder_L, 90, 40);
        //         // motor_6612_robot_forward_encoder(&motor_robot_6612, &enkoder_R, &enkoder_L, 200, 80);
        //         if (motor_robot_6612.status_dc == STOP_){
        //             engle_temp = engle_temp * -1;

        //         }
        //         motor_6612_robot_forward_turn_enkoder(&motor_robot_6612, &enkoder_R, &enkoder_L, engle_temp, 50, 40);

        //         printf("R:%d, L:%d||| LmK:%d, RmK:%d \r\n ", enkoder_R.count, enkoder_L.count, motor_robot_6612.k_L, motor_robot_6612.k_R);
                 printf("adc 26 = %d\r\n",sensor.state_a[0]);
                 sleep_ms(500);
                 //adc_read();
                  
        //         // motor_6612_robot_forward(&motor_robot_6612, 30);
        //         time_old_stamp = time_stamp;
        //     // } else {
        //     //     temp = 1;
        //     //     gpio_put(PICO_DEFAULT_LED_PIN, false);
        //     //     // motor_6612_robot_stop(&motor_robot_6612);
        //     //     time_old_stamp = time_stamp;
        //     // }
        // }
    }
}
