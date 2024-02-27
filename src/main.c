#include "sensor.h"
// #include "motor_dc_pwm.h"
#include "motor_robot.h"
#include "enkoder.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/watchdog.h"
// #include <stdio.h>
#include "move_on_line.h"


//-------------------init strukt for modul---------------------//

uint temp_gpio[] = {26,27,28};
uint16_t temp_data_analog[3];
sensor_t sensor = {
    .gpio = temp_gpio,
    .len = 3,
    .mode = ANALOG_sensor,
    .state_a = temp_data_analog,

};

motor_dc_pwm_6612_t  motor_robot_6612 = {
    .gpio_Lin1 = 8, // a=l
    .gpio_Lin2 = 9, // b=r
    .gpio_Rin1 = 7,
    .gpio_Rin2 = 6,
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

 //-------------------init---------------------///

void main_init(){
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    if (watchdog_caused_reboot()) printf("Rebooted by Watchdog!\n");
    watchdog_enable(100, 1);

    motor_6612_robot_init(&motor_robot_6612);
    enkoder_init(&enkoder_L, &enkoder_R);
    sensor_init(&sensor);
    move_line_init(&sensor, &motor_robot_6612)
}

 //-------------------main cycle---------------------//

int main() {
    main_init();
    int engle_temp = 360;
    // gpio_put(PICO_DEFAULT_LED_PIN, false);
    while (true) {
        static uint32_t time_stamp;
        static uint32_t time_old_stamp;

        time_stamp = time_us_32(); //  125.000 ≈ 1mc
        if  (time_stamp - time_old_stamp > 5000){ // 5000
            watchdog_update();
           

            ///// user code begin //////------------------------------------


             
            if (motor_robot_6612.status_dc == STOP_){
                engle_temp = engle_temp * -1;
            }
            motor_6612_robot_forward_turn_enkoder(&motor_robot_6612, &enkoder_R, &enkoder_L, engle_temp, 50, 30);





            


            ////// user code  end //////----------------------------------

            // printf("R:%d, L:%d||| LmK:%d, RmK:%d \r\n ", enkoder_R.count, enkoder_L.count, motor_robot_6612.k_L, motor_robot_6612.k_R);
            // printf("adc =%hu//%hu//%hu\r\n",sensor.state_a[0], sensor.state_a[1], sensor.state_a[2]);
            time_old_stamp = time_stamp;
           
        }
    }
}
