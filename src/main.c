#include "Bobla_sensor_line_lib.h"
// #include "motor_dc_pwm.h"
// #include "motor_robot.h"
#include "Bobla_encoder_lib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/watchdog.h"
#include "move_on_line.h"
#include "driver_motor_encoder.h"
#include "Bobla_6612_motor_lib.h"
#include "Bobla_brawls_sensor_lib.h"


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
    .flag_stop = 0,
};

enkoder_t enkoder_L = {
    .gpio = 19,
};
enkoder_t enkoder_R = {
    .gpio = 18,
};

uint braw_gpio_mas[] = {21,22,23};
bobla_brawls_sensor_t brawls_sensor = {
    .gpio = braw_gpio_mas,
    .len_gpio = 3,
    .state = 0,
};

 //-------------------init---------------------///

void main_init(){
    stdio_init_all();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    if (watchdog_caused_reboot()) printf("Rebooted by Watchdog!\n");
    watchdog_enable(100, 1);
    // motor_robot_init(&motor_robot_6612, &enkoder_R, &enkoder_L);
    driver_motor_init(&motor_robot_6612, &enkoder_R, &enkoder_L);
    enkoder_init_NO_irq(&enkoder_L, &enkoder_R);
    sensor_init(&sensor);
    move_line_init(&sensor);
    brawls_sensor_init(&brawls_sensor);
    gpio_init(24);
    gpio_set_dir(24, GPIO_OUT);
}

 //-------------------main cycle---------------------//

int main() {
    main_init();
    int engle_temp = 360;
   
    // gpio_put(PICO_DEFAULT_LED_PIN, false);
    while (true) {
        static uint32_t time_stamp;
        static uint32_t time_old_stamp;
        static uint32_t time_old_stamp_2;
        static uint32_t time_old_stamp_3;
        static bool flag_brawls_mode = false;

        time_stamp = time_us_32(); 
        if  (time_stamp - time_old_stamp > 5000){  //200Hz
            gpio_put(24, true);
            watchdog_update();
          
            /////--------------------------------- user code begin ---------------------------------//////
            enkoder_core_no_irq();

           
            time_old_stamp = time_stamp;
            gpio_put(24, false);
        }
        if  (time_stamp - time_old_stamp_2 > 20000){  //50Hz
            brawls_sensor_read();
            // printf("flag_brawls_mode == %d\r\n", brawls_sensor.state);
            if  (flag_brawls_mode == false){
                move_line_core();
                
                if (brawls_sensor.state != 0){ 
                    flag_brawls_mode = true;
                }
            }else{
                move_brawls_core(&brawls_sensor);
            }
            time_old_stamp_2 = time_stamp;
        }


        if  (time_stamp - time_old_stamp_3 > 500000){ //2.5Hz
            printf("rmpL = %d   ;rmpR = %d ", enkoder_L.rmp,enkoder_R.rmp);
            // printf("R:%d, L:%d||| LmK:%d, RmK:%d \r\n ", enkoder_R.count, enkoder_L.count, motor_robot_6612.k_L, motor_robot_6612.k_R);
            printf("sensor line =%d//%d//%d\r\n",sensor.state_a[0], sensor.state_a[1], sensor.state_a[2]);
            time_old_stamp_3 = time_stamp;
        }

        //////---------------------------------- user code  end ----------------------------------//////
    }
}