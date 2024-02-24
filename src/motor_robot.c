#include "motor_robot.h"

// #include "motor_dc_pwm.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"


// #include <stdlib.h>
uint motor_slise_rec;

//------------------------irq---------------------//

void on_pwm_wrap1() {
    pwm_clear_irq(motor_slise_rec);
    gpio_put(PICO_DEFAULT_LED_PIN, true);
}


//------------------------low-level-fun---------------------//


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
    pwm_clear_irq(slice_num);
    motor_slise_rec = slice_num;

    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap1);
    irq_set_enabled(PWM_IRQ_WRAP, true);
}
void motor_6612_robot_forward(motor_dc_pwm_6612_t* motor_robot, uint16_t speed){
    // if (motor_robot->status_dc != FORWARD){
    //     motor_robot->status_dc = FORWARD;
        gpio_put(motor_robot->gpio_Lin1, false);
        gpio_put(motor_robot->gpio_Lin2, true);
        gpio_put(motor_robot->gpio_Rin1, true);
        gpio_put(motor_robot->gpio_Rin2, false);
        gpio_put(motor_robot->gpio_stby, true);
    // }
    motor_robot->speed_req = speed;
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


//------------------------motor_whis_encoder---------------------//


void motor_6612_robot_forward_encoder(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L, uint len, uint speed){
    // enkoder_read(enkoder_R);
    // enkoder_read(enkoder_L);
    if(motor_robot->status_dc != FORWARD){
       // delta_K = ((float)radius-half_width)/((float)radius+half_width);
        enkoder_L->count = 0;
        enkoder_R->count = 0;
        motor_robot->status_dc = FORWARD;
    }
    static uint speed_control = 1700;
    if (enkoder_L->count > len * 2){
        motor_6612_robot_stop(motor_robot);
        speed_control = 1700;
        return;
    }
    motor_robot->k_R = (enkoder_L->count - enkoder_R->count) * 50;
    motor_robot->k_L = (enkoder_R->count - enkoder_L->count) * 50;

    if (speed_control < speed*100 + 1){
        speed_control += 50;
    }
    motor_6612_robot_forward(motor_robot, speed_control); 
}

void motor_6612_robot_turn_encoder(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L, uint engle, uint speed){
    engle = 30;// engle / 3;
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
void motor_6612_robot_forward_turn_enkoder(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L, int engle, uint speed, int radius){
    static uint speed_control = 1700;
    const float half_width = 5.7f;
    static float delta_K;
    
    static int enkoder_count_delta;

    if(motor_robot->status_dc != FORWARD_TURN){
        delta_K = ((((float)radius+half_width)/((float)radius-half_width)-1)/2)+1;
        enkoder_L->count = 0;
        enkoder_R->count = 0;
        speed_control = 1700;
        motor_robot->status_dc = FORWARD_TURN;
    }
    if (engle > 0){
        if ((enkoder_L->count + enkoder_R->count) > (int)((6.28f/360.0f)*(float)(radius*engle) * 4.f * 1.03f*0.966f)){
            printf("R:%d, L:%d   %f   %d| \r\n ", enkoder_R->count, enkoder_L->count, delta_K, enkoder_count_delta);
            motor_6612_robot_stop(motor_robot);
            return;
        }
        // enkoder_count_delta = (int)(delta_K * (float)(enkoder_R->count));
        static int enkoder_R_buf; //= (int)((float)(enkoder_R->count)*delta_K)
        static int enkoder_L_buf; //= (int)((float)(enkoder_L->count)/delta_K)
        enkoder_R_buf = (int)((float)(enkoder_R->count)*delta_K);
        enkoder_L_buf = (int)((float)(enkoder_L->count)/delta_K);
        motor_robot->k_L = (enkoder_R_buf - enkoder_L_buf+2) * 240;
        motor_robot->k_R = (enkoder_L_buf - enkoder_R_buf-2) * 240;
    } else {
        if ((enkoder_R->count + enkoder_L->count) > (int)((6.28f/360.0f)*(float)(radius*(engle*-1)) * 4.f * 0.966f)){
            printf("R:%d, L:%d|   %f   %d\r\n ", enkoder_R->count, enkoder_L->count, delta_K, enkoder_count_delta);
            motor_6612_robot_stop(motor_robot);
            return;
        }
        // enkoder_count_delta = (int)(delta_K * (float)(enkoder_L->count));
        static int enkoder_R_buf; //= (int)((float)(enkoder_R->count)/delta_K)
        static int enkoder_L_buf; //= (int)((float)(enkoder_L->count)*delta_K)
        enkoder_R_buf = (int)((float)(enkoder_R->count)/delta_K);
        enkoder_L_buf = (int)((float)(enkoder_L->count)*delta_K);
        motor_robot->k_L = (enkoder_R_buf - enkoder_L_buf-2) * 240;
        motor_robot->k_R = (enkoder_L_buf - enkoder_R_buf+2) * 240;
    }
     if (speed_control < speed * 100 + 1){
        //speed_control += 50;
        speed_control = 4000;
    }
    motor_6612_robot_forward(motor_robot, speed_control); 
}