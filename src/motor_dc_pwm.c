#include "motor_dc_pwm.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include <stdlib.h>
motor_dc_pwm_t* motor_reg[2];
void on_pwm_wrap() {
   
    
    uint slice_num_A = pwm_gpio_to_slice_num(motor_reg[0]->gpioA);
    pwm_clear_irq(slice_num_A);

    if (abs(motor_reg[0]->speed_req - motor_reg[0]->speed) > 0){
        if (motor_reg[0]->speed_req > motor_reg[0]->speed){
            motor_reg[0]->speed += 1;
            pwm_set_chan_level(slice_num_A, PWM_CHAN_A, motor_reg[0]->speed);

        }
    }
}

void motor_init(motor_dc_pwm_t* motor){
    // pwm_config config = pwm_get_default_config();
    // pwm_config_set_clkdiv(&config, 4.f);
    motor_reg[0] = motor;

    gpio_set_function(motor->gpioA, GPIO_FUNC_PWM);
    gpio_set_function(motor->gpioB, GPIO_FUNC_PWM);
    uint slice_num_A = pwm_gpio_to_slice_num(motor->gpioA);
    pwm_set_wrap(slice_num_A, 100);
    // pwm_set_chan_level(slice_num_A, 50, motor->gpioA);
    
    uint slice_num_B = pwm_gpio_to_slice_num(motor->gpioB);
    // pwm_set_chan_level(slice_num_B, 50, motor->gpioB);
    // pwm_init(slice_num_A, &config, true);
    // if (motor->gpioB - motor->gpioA != 1){
    //     pwm_set_wrap(slice_num_B, 100);
    //     // pwm_init(slice_num_B, &config, true);
    // }
    // pwm_clear_irq(slice_num_A);
    

}

void motor_start(motor_dc_pwm_t* motor){
    motor->status = START;
    uint slice_num_A = pwm_gpio_to_slice_num(motor->gpioA);
    uint slice_num_B = pwm_gpio_to_slice_num(motor->gpioB);
    if (motor->direct == CCW){
        pwm_set_chan_level(slice_num_A, PWM_CHAN_A, motor->speed);
        // pwm_set_chan_level(slice_num_B, PWM_CHAN_A, motor->speed);
        pwm_set_gpio_level(motor->gpioB, 0);
    } else {
        pwm_set_chan_level(slice_num_B, PWM_CHAN_B, motor->speed);
        // pwm_set_gpio_level(motor->gpioA, 0);
    }
    pwm_set_enabled(slice_num_A, true);
    if (motor->gpioB - motor->gpioA != 1)   pwm_set_enabled(slice_num_B, true);
}

void motor_stop(motor_dc_pwm_t* motor){
    motor->status = STOP;
    pwm_set_gpio_level(motor->gpioA, 0);
    pwm_set_gpio_level(motor->gpioB, 0);
}
void motor_brake(motor_dc_pwm_t* motor){
    motor->status = BRAKE;
    pwm_set_gpio_level(motor->gpioA, 1);
    pwm_set_gpio_level(motor->gpioB, 1);
    
}

