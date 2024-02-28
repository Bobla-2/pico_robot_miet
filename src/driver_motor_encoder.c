#include "driver_motor_encoder.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "enkoder.h"

motor_dc_pwm_6612_t* en_dr_motor;
enkoder_t* en_dr_encoder_r;
enkoder_t* en_dr_encoder_l;
uint motor_dr_slise_rec;

//------------------------irq---------------------//

void on_pwm_driver() {
    pwm_clear_irq(motor_dr_slise_rec);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
}

//------------------------low-level-fun---------------------//


void driver_motor_6612_robot_init(motor_dc_pwm_6612_t* motor_robot){
    gpio_init(motor_robot->gpio_Lin1);
    gpio_init(motor_robot->gpio_Lin2);
    gpio_init(motor_robot->gpio_Rin1);
    gpio_init(motor_robot->gpio_Rin2);
    gpio_init(motor_robot->gpio_stby);
   
    gpio_set_dir(motor_robot->gpio_Lin1, GPIO_OUT);
    gpio_set_dir(motor_robot->gpio_Lin2, GPIO_OUT);
    gpio_set_dir(motor_robot->gpio_Rin1, GPIO_OUT);
    gpio_set_dir(motor_robot->gpio_Rin2, GPIO_OUT);
    gpio_set_dir(motor_robot->gpio_stby, GPIO_OUT);
    gpio_set_function(motor_robot->gpio_Lpwm, GPIO_FUNC_PWM);
    gpio_set_function(motor_robot->gpio_Rpwm, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
    pwm_set_wrap(slice_num, 10000);
    pwm_clear_irq(slice_num);
    motor_dr_slise_rec = slice_num;
    wm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_driver);
    irq_set_enabled(PWM_IRQ_WRAP, true);
}


void driver_6612_motor_move(uint speed_R, uint speed_L){
    gpio_put(en_dr_motor->gpio_Lin1, false);
    gpio_put(en_dr_motor->gpio_Lin2, true);
    gpio_put(en_dr_motor->gpio_Rin1, true);
    gpio_put(en_dr_motor->gpio_Rin2, false);
    gpio_put(en_dr_motor->gpio_stby, true);
    
    uint slice_num = pwm_gpio_to_slice_num(en_dr_motor->gpio_Rpwm);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, speed_L*100);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, speed_R*100);
    pwm_set_enabled(slice_num, true);
}


//------------------------motor_whis_encoder---------------------//
void driver_motor_init(motor_dc_pwm_6612_t* motor_conf, enkoder_t* enkoder_R, enkoder_t* enkoder_L){
    motor_6612_robot_init(motor_conf);
    en_dr_motor = motor_conf;
    en_dr_encoder_l = enkoder_L;
    en_dr_encoder_r = enkoder_R;
}

void driver_motor_forward(uint speed){
    driver_6612_motor_move(speed, speed);
}

void driver_motor_forward_left(uint level, uint speed){
    uint temp_level = speed - (level *speed / 100);
    driver_6612_motor_move(speed, temp_level);
    
    

}
void driver_motor_forward_right(uint level, uint speed){
    uint temp_level = speed - (level *speed / 100);
    driver_6612_motor_move(temp_level, speed);

}
void driver_motor_stop(){
    driver_6612_motor_move(0,0);

}