#include "sensor.h"
// #include "motor_dc_pwm.h"
#include "motor_robot.h"
#include "enkoder.h"
// #include <stdio.h>

uint temp_gpio[] = {20,21,22};
sensor_t state_sensor = {
    .gpio = temp_gpio,
    .len = 3,
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
    .gpio = 23,
};
enkoder_t enkoder_R = {
    .gpio = 22,
};

void main_init(){
    stdio_init_all();
    sensor_init(&state_sensor);

    // motor_robot_init(&motor_robot);
    motor_6612_robot_init(&motor_robot_6612);
    // motor_init(&motor_dc_L);
    // motor_dc_L.speed_req = 50;
    // motor_start(&motor_dc_L);
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main() {
    
    main_init();
    
    while (true) {
        static uint32_t time_stamp;
        static uint32_t time_old_stamp;
        // static uint32_t temp;
        // static char temp_str[128];
        time_stamp = time_us_32(); //  125.000 ≈ 1mc
        if  (time_stamp - time_old_stamp > 5000){
            // if  (temp == 1){
                // temp = 0;
                gpio_put(PICO_DEFAULT_LED_PIN, true);
                // motor_6612_robot_forward_turn_encoder(&motor_robot_6612, &enkoder_R, &enkoder_L, 90, 40);
                motor_6612_robot_forward_encoder(&motor_robot_6612, &enkoder_R, &enkoder_L, 200, 30);
                
                printf("R:%d, L:%d||| LmK:%d, RmK:%d \r\n ", enkoder_R.count, enkoder_L.count, motor_robot_6612.k_L, motor_robot_6612.k_R);
                // motor_6612_robot_forward(&motor_robot_6612, 30);
                time_old_stamp = time_stamp;
            // } else {
            //     temp = 1;
            //     gpio_put(PICO_DEFAULT_LED_PIN, false);
            //     // motor_6612_robot_stop(&motor_robot_6612);
            //     time_old_stamp = time_stamp;
            // }
        }
    }
}
