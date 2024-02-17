#include "motor_robot.h"

// #include "motor_dc_pwm.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"


// #include <stdlib.h>
motor_robot_t* motor_rob_rec;
void on_pwm_wrap1() {
    // uint16_t static temp = 0;
    uint slice_num_L = pwm_gpio_to_slice_num(motor_rob_rec->motor_L->gpioA);
    // uint slice_num_R = pwm_gpio_to_slice_num(motor_rob_rec->motor_R->gpioA);
    pwm_clear_irq(slice_num_L);
    // pwm_clear_irq(slice_num_R);
    // temp += 1;
    // pwm_set_chan_level(slice_num_L, PWM_CHAN_A, temp);
    // const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // if (temp == 0){
    //     temp = 1;
    gpio_put(PICO_DEFAULT_LED_PIN, true);
    //     // pwm_set_chan_level(slice_num_L, PWM_CHAN_A, 9000);
    // }
    // pwm_clear_irq(slice_num_R);
    // motor_rob_rec->motor_L->speed += 1;
    // pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_rob_rec->motor_L->speed);
    // switch (motor_rob_rec->status_dc){
    //     case FORWARD:

    //         // if (motor_rob_rec->motor_L->speed_req > motor_rob_rec->motor_L->speed){
                
    //             //     motor_rob_rec->motor_L->speed += 1;
    //             //     pwm_set_chan_level(slice_num_L, PWM_CHAN_A, motor_rob_rec->motor_L->speed);
    //             //     pwm_set_chan_level(slice_num_L, PWM_CHAN_B, motor_rob_rec->motor_L->speed);
    //             // // }
    //             // if (motor_rob_rec->motor_R->speed_req > motor_rob_rec->motor_R->speed){
                
    //             //     motor_rob_rec->motor_R->speed += 1;
    //             //     pwm_set_chan_level(slice_num_R, PWM_CHAN_A, motor_rob_rec->motor_R->speed);
    //             //     pwm_set_chan_level(slice_num_R, PWM_CHAN_B, motor_rob_rec->motor_R->speed);
    //             // }
    //         break;
    //     case FORWARD_TURN:
    //         break;
    //     // case TURN_L:
    //     //     if (motor_rob_rec->motor_R->speed_req < motor_rob_rec->motor_R->speed){
    //     //             motor_rob_rec->motor_R->speed += 1;
    //     //             pwm_set_chan_level(slice_num_R, PWM_CHAN_B, motor_rob_rec->motor_R->speed);
    //     //         }
    //     //     break;
    //     // case TURN_R:
    //     //     if (motor_rob_rec->motor_L->speed_req < motor_rob_rec->motor_L->speed){
                
    //     //             motor_rob_rec->motor_L->speed += 1;
    //     //             pwm_set_chan_level(slice_num_L, PWM_CHAN_A, motor_rob_rec->motor_L->speed);
    //     //         }
    //     //     break;
    //     case TURN_SPOT:
    //         break;
    //     case BACK:
    //         break;

        
        
    //     default:
    //         break;
    // }
    
}

void motor_init(motor_dc_pwm_t* motor){
    gpio_set_function(motor->gpioA, GPIO_FUNC_PWM);
    gpio_set_function(motor->gpioB, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(motor->gpioA);
    pwm_set_wrap(slice_num, 10000);
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    
}

void motor_start(motor_dc_pwm_t* motor){
    motor->status_dc = START;
    uint slice_num_A = pwm_gpio_to_slice_num(motor->gpioA);
    uint slice_num_B = pwm_gpio_to_slice_num(motor->gpioB);
    if (motor->direct == CCW){
        motor->speed = 100;
        pwm_set_chan_level(slice_num_A, PWM_CHAN_A, motor->speed_req);
        pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0);
        // pwm_set_gpio_level(motor->gpioB, 0);
    } else if (motor->direct == CW){
        pwm_set_chan_level(slice_num_B, PWM_CHAN_B, motor->speed_req);
        pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0);
        // pwm_set_gpio_level(motor->gpioA, 0);
    }
    
    pwm_set_enabled(slice_num_A, true);
    if (motor->gpioB - motor->gpioA != 1)   pwm_set_enabled(slice_num_B, true);
    // irq_set_enabled(PWM_IRQ_WRAP, true);
    // if(motor->gpioA == 2){
    // pwm_clear_irq(slice_num_A);
    // pwm_set_irq_enabled(slice_num_A, true);
    // irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap1);
    // irq_set_enabled(PWM_IRQ_WRAP, true);
    // }
}

void motor_stop(motor_dc_pwm_t* motor){
    motor->status_dc = STOP;
    uint slice_num_A = pwm_gpio_to_slice_num(motor->gpioA);
    uint slice_num_B = pwm_gpio_to_slice_num(motor->gpioB);
    pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 0);
    pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 0);
    // pwm_set_gpio_level(motor->gpioA, 0);
    // pwm_set_gpio_level(motor->gpioB, 0);
}
void motor_brake(motor_dc_pwm_t* motor){
    motor->status_dc = BRAKE;
    uint slice_num_A = pwm_gpio_to_slice_num(motor->gpioA);
    uint slice_num_B = pwm_gpio_to_slice_num(motor->gpioB);
    pwm_set_chan_level(slice_num_A, PWM_CHAN_A, 10000);
    pwm_set_chan_level(slice_num_B, PWM_CHAN_B, 10000);
}



void motor_robot_init(motor_robot_t* motor_robot){
    motor_init(motor_robot->motor_L);
    motor_init(motor_robot->motor_R);
    // pwm_config config = pwm_get_default_config();
    // pwm_config_set_clkdiv(&config, 4.f);
    // uint slice_num = pwm_gpio_to_slice_num(motor_robot->motor_L->gpioA);
    // pwm_init(slice_num, &config, true);
    
}

void motor_robot_forward(motor_robot_t* motor_robot, uint16_t speed){
    motor_robot->status_dc = FORWARD;
    motor_robot->motor_L->speed_req = speed*100;
    motor_robot->motor_R->speed_req = speed*100;
    motor_robot->motor_L->direct = CCW;
    motor_robot->motor_R->direct = CCW;
    motor_start(motor_robot->motor_L);
    motor_start(motor_robot->motor_R);
}

void motor_robot_turn(motor_robot_t* motor_robot, uint DIR){
    
    if (DIR == ROBOT_CW){
        motor_robot->status_dc = TURN_R;
        motor_robot->motor_L->speed_req = 1000;
        motor_robot->motor_L->direct = CCW;
        motor_start(motor_robot->motor_L);
        motor_brake(motor_robot->motor_R);
    } else if (DIR == ROBOT_CCW){
        motor_robot->status_dc = TURN_L;
        motor_robot->motor_R->speed_req = 1000;
        motor_robot->motor_R->direct = CCW;
        motor_start(motor_robot->motor_R);
        motor_brake(motor_robot->motor_L);
    }
    
}
void motor_robot_stop(motor_robot_t* motor_robot){
    motor_robot->status_dc = STOP_;
    motor_stop(motor_robot->motor_L);
    motor_stop(motor_robot->motor_R);
}

void motor_robot_turn_spot(motor_robot_t* motor_robot, uint DIR){
    
    if (DIR == ROBOT_CW){
        motor_robot->status_dc = TURN_SPOT_R;
        motor_robot->motor_L->speed = 1000;
        motor_robot->motor_L->direct = CCW;
        motor_start(motor_robot->motor_L);
        motor_robot->motor_L->speed = 1000;
        motor_robot->motor_L->direct = CW;
        motor_start(motor_robot->motor_L);
    } else if (DIR == ROBOT_CCW){
        motor_robot->status_dc = TURN_SPOT_L;
        motor_robot->motor_R->speed = 1000;
        motor_robot->motor_R->direct = CW;
        motor_start(motor_robot->motor_R);
        motor_robot->motor_L->speed = 1000;
        motor_robot->motor_L->direct = CCW;
        motor_start(motor_robot->motor_L);
    }
}
void motor_robot_back(motor_robot_t* motor_robot){
    motor_robot->motor_L->speed_req = 1000;
    motor_robot->motor_R->speed_req = 1000;
    motor_robot->motor_L->direct = CW;
    motor_robot->motor_R->direct = CW;
    motor_start(motor_robot->motor_L);
    motor_start(motor_robot->motor_R);
}
void motor_robot_forward_turn(motor_robot_t* motor_robot, uint DIR, uint engle){

}


//---------------------------------------------


void motor_6612_robot_init(motor_dc_pwm_6612_t* motor_robot){
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
}
void motor_6612_robot_forward(motor_dc_pwm_6612_t* motor_robot, uint16_t speed){
    motor_robot->status_dc = FORWARD;
    gpio_put(motor_robot->gpio_Lin1, false);
    gpio_put(motor_robot->gpio_Lin2, true);
    gpio_put(motor_robot->gpio_Rin1, true);
    gpio_put(motor_robot->gpio_Rin2, false);
    gpio_put(motor_robot->gpio_stby, true);
    motor_robot->speed_req = speed*100;
    uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Rpwm);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
    pwm_set_enabled(slice_num, true);
   
}

void motor_6612_robot_turn_spot(motor_dc_pwm_6612_t* motor_robot, uint DIR){
    uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
    
    gpio_put(motor_robot->gpio_stby, true);
    motor_robot->speed_req = 20*100;
    if (DIR == ROBOT_CCW){
        motor_robot->status_dc = TURN_SPOT_L;
        gpio_put(motor_robot->gpio_Lin1, false);
        gpio_put(motor_robot->gpio_Lin2, true);
        gpio_put(motor_robot->gpio_Rin1, false);
        gpio_put(motor_robot->gpio_Rin2, true);
        
        uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
        pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
        pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
    } else if (DIR == ROBOT_CW){
        motor_robot->status_dc = TURN_SPOT_R;
        gpio_put(motor_robot->gpio_Lin1, true);
        gpio_put(motor_robot->gpio_Lin2, false);
        gpio_put(motor_robot->gpio_Rin1, true);
        gpio_put(motor_robot->gpio_Rin2, false);
        motor_robot->status_dc = TURN_R;
        pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
        pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
    }
    pwm_set_enabled(slice_num, true);
}

void motor_6612_robot_turn(motor_dc_pwm_6612_t* motor_robot, uint DIR){
    uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
    gpio_put(motor_robot->gpio_Lin1, false);
    gpio_put(motor_robot->gpio_Rin1, false);
    gpio_put(motor_robot->gpio_stby, true);
    motor_robot->speed_req = 20*100;
    if (DIR == ROBOT_CCW){
        gpio_put(motor_robot->gpio_Lin2, false);
        gpio_put(motor_robot->gpio_Rin2, true);
        motor_robot->status_dc = TURN_L;
        uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
        pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
    } else if (DIR == ROBOT_CW){
        gpio_put(motor_robot->gpio_Lin2, true);
        gpio_put(motor_robot->gpio_Rin2, false);
        motor_robot->status_dc = TURN_R;
        pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
    }
    pwm_set_enabled(slice_num, true);
}
void motor_6612_robot_stop(motor_dc_pwm_6612_t* motor_robot){
    motor_robot->status_dc = STOP_;
    gpio_put(motor_robot->gpio_Lin1, false);
    gpio_put(motor_robot->gpio_Lin2, false);
    gpio_put(motor_robot->gpio_Rin1, false);
    gpio_put(motor_robot->gpio_Rin2, false);
    uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
    gpio_put(motor_robot->gpio_Lpwm, false);
    gpio_put(motor_robot->gpio_Rpwm, false);
    pwm_set_enabled(slice_num, false);
}
void motor_6612_robot_back(motor_dc_pwm_6612_t* motor_robot){
    motor_robot->status_dc = BACK;
    gpio_put(motor_robot->gpio_Lin1, true);
    gpio_put(motor_robot->gpio_Lin2, false);
    gpio_put(motor_robot->gpio_Rin1, false);
    gpio_put(motor_robot->gpio_Rin2, true);
    gpio_put(motor_robot->gpio_stby, true);
    motor_robot->status_dc = FORWARD;
    motor_robot->speed_req = 20*100;
    uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req + motor_robot->k_L);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req + motor_robot->k_R);
    pwm_set_enabled(slice_num, true);
}

void motor_6612_robot_forward_encoder(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L, uint len, uint speed){
    enkoder_read(enkoder_R);
    enkoder_read(enkoder_L);
    // static bool flagg;
    if (enkoder_L->count > len){
        motor_6612_robot_stop(motor_robot);
        
        return;
    }
    motor_robot->k_R = (enkoder_L->count - enkoder_R->count) * 100;
    motor_robot->k_L = (enkoder_R->count - enkoder_L->count) * 100;
   
    motor_6612_robot_forward(motor_robot, speed); 
}

void motor_6612_robot_forward_turn_encoder(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L, uint engle, uint speed){
    enkoder_read(enkoder_R);
    enkoder_read(enkoder_L);
    engle = 30;// engle / 3;
    // static bool sdf;
    // if (sdf == false){
    //     sdf = true;
    //     enkoder_L->count = 0;
    //     enkoder_R->count = 0;
    // }
    
    
    uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
    
    gpio_put(motor_robot->gpio_stby, true);
    motor_robot->speed_req = 20*100;
    if (engle < 0){
        if (enkoder_R->count >= engle){
            motor_6612_robot_stop(motor_robot);
            return;
        }
        gpio_put(motor_robot->gpio_Lin1, false);
        gpio_put(motor_robot->gpio_Rin1, false);
        gpio_put(motor_robot->gpio_Lin2, false);
        gpio_put(motor_robot->gpio_Rin2, true);
        motor_robot->status_dc = TURN_L;
        uint slice_num = pwm_gpio_to_slice_num(motor_robot->gpio_Lpwm);
        pwm_set_chan_level(slice_num, PWM_CHAN_A, motor_robot->speed_req);
    } else if (engle > 0){
        if (enkoder_L->count >= engle){
            motor_6612_robot_stop(motor_robot);
            return;
        }
        gpio_put(motor_robot->gpio_Lin1, true);
        gpio_put(motor_robot->gpio_Rin1, false);
        gpio_put(motor_robot->gpio_Lin2, false);
        gpio_put(motor_robot->gpio_Rin2, false);
        motor_robot->status_dc = TURN_R;
        pwm_set_chan_level(slice_num, PWM_CHAN_B, motor_robot->speed_req);
    } else return;
    pwm_set_enabled(slice_num, true);
}
// void motor_6612_robot_forward_turn(motor_dc_pwm_6612_t* motor_robot, uint DIR, uint engle);