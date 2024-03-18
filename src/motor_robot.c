// #include "motor_robot.h"

// // #include "motor_dc_pwm.h"
// #include "pico/time.h"
// #include "hardware/irq.h"
// #include "hardware/pwm.h"

// motor_dc_pwm_6612_t* en_motor;
// enkoder_t* en_encoder_r;
// enkoder_t* en_encoder_l;
// uint motor_slise_rec;

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


// //------------------------motor_whis_encoder---------------------//


// void motor_robot_init(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L){
//     motor_6612_robot_init(motor_robot);
//     en_motor = motor_robot;
//     en_encoder_l = enkoder_L;
//     en_encoder_r = enkoder_R;
// }

// void motor_robot_forward_encoder( uint len, uint speed){
//     if(en_motor->status_dc != FORWARD){
//         en_encoder_l->count = 0;
//         en_encoder_r->count = 0;
//         en_motor->status_dc = FORWARD;
//     }
//     static uint speed_control = 1700;
//     if (en_encoder_l->count > len * 2){
//         motor_6612_robot_stop(en_motor);
//         speed_control = 1700;
//         return;
//     }
//     en_motor->k_R = (en_encoder_l->count - en_encoder_r->count) * 50;
//     en_motor->k_L = (en_encoder_r->count - en_encoder_l->count) * 50;

//     if (speed_control < speed*100 + 1){
//         speed_control += 50;
//     }
//     motor_6612_robot_forward(en_motor, speed_control); 
// }

// void motor_robot_turn_encoder(uint engle, uint speed){
//     engle = 30;// engle / 3;
//     uint slice_num = pwm_gpio_to_slice_num(en_motor->gpio_Lpwm);
    
//     gpio_put(en_motor->gpio_stby, true);
//     en_motor->speed_req = 20*100;
//     if (engle < 0){
//         if (en_encoder_r->count >= engle){
//             motor_6612_robot_stop(en_motor);
//             return;
//         }
//         gpio_put(en_motor->gpio_Lin1, false);
//         gpio_put(en_motor->gpio_Rin1, false);
//         gpio_put(en_motor->gpio_Lin2, false);
//         gpio_put(en_motor->gpio_Rin2, true);
//         en_motor->status_dc = TURN_L;
//         uint slice_num = pwm_gpio_to_slice_num(en_motor->gpio_Lpwm);
//         pwm_set_chan_level(slice_num, PWM_CHAN_A, en_motor->speed_req);
//     } else if (engle > 0){
//         if (en_encoder_l->count >= engle){
//             motor_6612_robot_stop(en_motor);
//             return;
//         }
//         gpio_put(en_motor->gpio_Lin1, true);
//         gpio_put(en_motor->gpio_Rin1, false);
//         gpio_put(en_motor->gpio_Lin2, false);
//         gpio_put(en_motor->gpio_Rin2, false);
//         en_motor->status_dc = TURN_R;
//         pwm_set_chan_level(slice_num, PWM_CHAN_B, en_motor->speed_req);
//     } else return;
//     pwm_set_enabled(slice_num, true);
// }
// void motor_robot_forward_turn_enkoder(int engle, uint speed, int radius, bool infinity_enable){
//     static uint speed_control = 1700;
//     const float half_width = 5.7f;
//     static float delta_K;
//     motor_robot_forward_turn_enkoder();
    
//     static int enkoder_count_delta;

//     if(en_motor->status_dc != FORWARD_TURN){
//         delta_K = ((((float)radius+half_width)/((float)radius-half_width)-1)/2)+1;
//         en_encoder_l->count = 0;
//         en_encoder_r->count = 0;
//         speed_control = 1700;
//         en_motor->status_dc = FORWARD_TURN;
//     }
//     if (engle > 0){
//         if (!infinity_enable){
//             if ((en_encoder_l->count + en_encoder_r->count) > (int)((6.28f/360.0f)*(float)(radius*engle) * 4.f * 1.03f*0.946f * ((radius*1.666f/1000.f)+0.9f))){
//                 printf("R:%d, L:%d   %f   %d| \r\n ", en_encoder_r->count, en_encoder_l->count, delta_K, enkoder_count_delta);
//                 motor_6612_robot_stop(en_motor);
//                 return;
//             }
//         }
//         int enkoder_R_buf;
//         int enkoder_L_buf;
//         enkoder_R_buf = (int)((float)(en_encoder_r->count)*delta_K);
//         enkoder_L_buf = (int)((float)(en_encoder_l->count)/delta_K);
//         en_motor->k_L = (enkoder_R_buf - enkoder_L_buf+2) * 240;
//         en_motor->k_R = (enkoder_L_buf - enkoder_R_buf-2) * 240;
//     } else {
//         if (!infinity_enable){
//             if ((en_encoder_r->count + en_encoder_l->count) > (int)((6.28f/360.0f)*(float)(radius*(engle*-1)) * 4.f * 0.944f * ((radius*1.666f/1000.f)+0.9f))){
//                 printf("R:%d, L:%d|   %f   %d\r\n ", en_encoder_r->count, en_encoder_l->count, delta_K, enkoder_count_delta);
//                 motor_6612_robot_stop(en_motor);
//                 return;
//             }
//         }
//         int enkoder_R_buf;
//         int enkoder_L_buf;
//         enkoder_R_buf = (int)((float)(en_encoder_r->count)/delta_K);
//         enkoder_L_buf = (int)((float)(en_encoder_l->count)*delta_K);
//         en_motor->k_L = (enkoder_R_buf - enkoder_L_buf-2) * 240;
//         en_motor->k_R = (enkoder_L_buf - enkoder_R_buf+2) * 240;
//     }
//      if (speed_control < speed * 100 + 1){
//         //speed_control += 50;
//         speed_control = 4000;
//     }
//     motor_6612_robot_forward(en_motor, speed_control); 
// }

// void motor_robot_stop(void){
//     motor_6612_robot_stop(en_motor);
// }