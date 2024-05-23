#include "Bobla_6612_motor_lib.h"

// #include "motor_dc_pwm.h"
// #include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"


uint motor_slise_rec;
uint motor_dr_slise_rec;
motor_dc_pwm_6612_t* bob_en_dr_motor;
// //------------------------irq---------------------//

// void on_pwm_wrap1() {
//     pwm_clear_irq(motor_slise_rec);
//     gpio_put(PICO_DEFAULT_LED_PIN, true);
// }

// //------------------------low-level-fun---------------------//


// void motor_6612_robot_init(motor_dc_pwm_6612_t* motor_robot){
//     gpio_init(motor_robot->gpio_Lin1);
//     gpio_init(motor_robot->gpio_Lin2);
//     gpio_init(motor_robot->gpio_Rin1);
//     gpio_init(motor_robot->gpio_Rin2);
//     gpio_init(motor_robot->gpio_stby);
   
//     gpio_set_dir(motor_robot->gpio_Lin1, GPIO_OUT);
//     gpio_set_dir(motor_robot->gpio_Lin2, GPIO_OUT);
//     gpio_set_dir(motor_robot->gpio_Rin1, GPIO_OUT);
//     gpio_set_dir(motor_robot->gpio_Rin2, GPIO_OUT);
//     gpio_set_dir(motor_robot->gpio_stby, GPIO_OUT);
//     gpio_set_function(motor_robot->gpio_Lpwm, GPIO_FUNC_PWM);
//     gpio_set_function(motor_robot->gpio_Rpwm, GPIO_FUNC_PWM);
//     uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
//     pwm_set_wrap(slice_num, 10000);
//     pwm_clear_irq(slice_num);
//     motor_slise_rec = slice_num;

//     pwm_set_irq_enabled(slice_num, true);
//     irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap1);
//     irq_set_enabled(PWM_IRQ_WRAP, true);
// }
// void motor_6612_robot_forward(motor_dc_pwm_6612_t* motor_robot, uint16_t speed){
//     gpio_put(motor_robot->gpio_Lin1, false);
//     gpio_put(motor_robot->gpio_Lin2, true);
//     gpio_put(motor_robot->gpio_Rin1, true);
//     gpio_put(motor_robot->gpio_Rin2, false);
//     gpio_put(motor_robot->gpio_stby, true);
    
//     motor_robot->speed_req = speed;
//     uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Rpwm);
//     pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
//     pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
//     pwm_set_enabled(slice_num, true);
    
   
// }

// void motor_6612_robot_turn_spot(motor_dc_pwm_6612_t* motor_robot, uint DIR){
//     uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
    
//     gpio_put(motor_robot->gpio_stby, true);
//     motor_robot->speed_req = 20*100;
//     if (DIR == ROBOT_CCW){
//         motor_robot->status_dc = TURN_SPOT_L;
//         gpio_put(motor_robot->gpio_Lin1, false);
//         gpio_put(motor_robot->gpio_Lin2, true);
//         gpio_put(motor_robot->gpio_Rin1, false);
//         gpio_put(motor_robot->gpio_Rin2, true);
        
//         uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
//         pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
//         pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
//     } else if (DIR == ROBOT_CW){
//         motor_robot->status_dc = TURN_SPOT_R;
//         gpio_put(motor_robot->gpio_Lin1, true);
//         gpio_put(motor_robot->gpio_Lin2, false);
//         gpio_put(motor_robot->gpio_Rin1, true);
//         gpio_put(motor_robot->gpio_Rin2, false);
//         motor_robot->status_dc = TURN_R;
//         pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
//         pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
//     }
//     pwm_set_enabled(slice_num, true);
// }

// void motor_6612_robot_turn(motor_dc_pwm_6612_t* motor_robot, uint DIR){
//     uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
//     gpio_put(motor_robot->gpio_Lin1, false);
//     gpio_put(motor_robot->gpio_Rin1, false);
//     gpio_put(motor_robot->gpio_stby, true);
//     motor_robot->speed_req = 20*100;
//     if (DIR == ROBOT_CCW){
//         gpio_put(motor_robot->gpio_Lin2, false);
//         gpio_put(motor_robot->gpio_Rin2, true);
//         motor_robot->status_dc = TURN_L;
//         uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
//         pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
//     } else if (DIR == ROBOT_CW){
//         gpio_put(motor_robot->gpio_Lin2, true);
//         gpio_put(motor_robot->gpio_Rin2, false);
//         motor_robot->status_dc = TURN_R;
//         pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
//     }
//     pwm_set_enabled(slice_num, true);
// }
// void motor_6612_robot_stop(motor_dc_pwm_6612_t* motor_robot){
//     motor_robot->status_dc = STOP_;
//     gpio_put(motor_robot->gpio_Lin1, false);
//     gpio_put(motor_robot->gpio_Lin2, false);
//     gpio_put(motor_robot->gpio_Rin1, false);
//     gpio_put(motor_robot->gpio_Rin2, false);
//     uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
//     pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
//     pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
//     gpio_put(motor_robot->gpio_Lpwm, false);
//     gpio_put(motor_robot->gpio_Rpwm, false);
//     pwm_set_enabled(slice_num, false);
// }
// void motor_6612_robot_back(motor_dc_pwm_6612_t* motor_robot){
//     motor_robot->status_dc = BACK;
//     gpio_put(motor_robot->gpio_Lin1, true);
//     gpio_put(motor_robot->gpio_Lin2, false);
//     gpio_put(motor_robot->gpio_Rin1, false);
//     gpio_put(motor_robot->gpio_Rin2, true);
//     gpio_put(motor_robot->gpio_stby, true);
//     motor_robot->status_dc = FORWARD;
//     motor_robot->speed_req = 20*100;
//     uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
//     pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
//     pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
//     pwm_set_enabled(slice_num, true);
// }
//------------------------irq---------------------//

void on_pwm_driver() {
    pwm_clear_irq(motor_dr_slise_rec);
    // gpio_put(PICO_DEFAULT_LED_PIN, true);
}

//------------------------low-level-fun---------------------//


void driver_motor_6612_robot_init(motor_dc_pwm_6612_t* motor_robot){
    bob_en_dr_motor = motor_robot;
    gpio_init(bob_en_dr_motor->gpio_Lin1);
    gpio_init(bob_en_dr_motor->gpio_Lin2);
    gpio_init(bob_en_dr_motor->gpio_Rin1);
    gpio_init(bob_en_dr_motor->gpio_Rin2);
    gpio_init(bob_en_dr_motor->gpio_stby);
   
    gpio_set_dir(bob_en_dr_motor->gpio_Lin1, GPIO_OUT);
    gpio_set_dir(bob_en_dr_motor->gpio_Lin2, GPIO_OUT);
    gpio_set_dir(bob_en_dr_motor->gpio_Rin1, GPIO_OUT);
    gpio_set_dir(bob_en_dr_motor->gpio_Rin2, GPIO_OUT);
    gpio_set_dir(bob_en_dr_motor->gpio_stby, GPIO_OUT);
    gpio_set_function(bob_en_dr_motor->gpio_Lpwm, GPIO_FUNC_PWM);
    gpio_set_function(bob_en_dr_motor->gpio_Rpwm, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(bob_en_dr_motor->gpio_Lpwm);
    pwm_set_wrap(slice_num, 10000);
    pwm_clear_irq(slice_num);
    motor_dr_slise_rec = slice_num;
//     if (bob_en_dr_motor->flag_enable_irq == true){
//         pwm_set_irq_enabled(slice_num, true);
//         irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_driver);
//         irq_set_enabled(PWM_IRQ_WRAP, true);
// }
    }
    



void driver_6612_motor_move(uint speed_R, uint speed_L, int DIR_R, int DIR_L){
    gpio_put(bob_en_dr_motor->gpio_Lin1, !(bool)DIR_L);
    gpio_put(bob_en_dr_motor->gpio_Lin2, (bool)DIR_L);
    
    gpio_put(bob_en_dr_motor->gpio_Rin1, (bool)DIR_R);
    gpio_put(bob_en_dr_motor->gpio_Rin2, !(bool)DIR_R);


    gpio_put(bob_en_dr_motor->gpio_stby, true);
    
    uint slice_num = pwm_gpio_to_slice_num(bob_en_dr_motor->gpio_Rpwm);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, speed_L*100);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, speed_R*100);
    pwm_set_enabled(slice_num, true);
}
