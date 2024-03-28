#include "driver_motor_encoder.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "Bobla_encoder_lib.h"

motor_dc_pwm_6612_t* en_dr_motor;
enkoder_t* en_dr_encoder_r;
enkoder_t* en_dr_encoder_l;


//------------------------motor_whis_encoder---------------------//
void driver_motor_init(motor_dc_pwm_6612_t* motor_conf, enkoder_t* enkoder_R, enkoder_t* enkoder_L){
    driver_motor_6612_robot_init(motor_conf);
    en_dr_motor = motor_conf;
    en_dr_encoder_l = enkoder_L;
    en_dr_encoder_r = enkoder_R;
}


void driver_motor_forward(uint speed){
    en_dr_motor->flag_stop = 0;
    printf("driver_motor_forward\r\n");
    driver_6612_motor_move(speed, speed, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_FORVERD);
}

void driver_motor_forward_left(uint level, uint speed){
    en_dr_motor->flag_stop = 0;
    uint temp_level = speed - (level *speed / 100);
    driver_6612_motor_move(speed, 0, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_FORVERD);
}

void driver_motor_forward_left_turn(uint level, uint speed){
    en_dr_motor->flag_stop = 0;
    // uint temp_level = speed - (level *speed / 100);
    driver_6612_motor_move(speed, speed+20, DRIVER_MOTOR_BACK, DRIVER_MOTOR_FORVERD);
}
void driver_motor_forward_right(uint level, uint speed){
    en_dr_motor->flag_stop = 0;
    uint temp_level = speed - (level *speed / 100);
    driver_6612_motor_move(0, speed, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_FORVERD);
}

void driver_motor_forward_right_turn(uint level, uint speed){
    // uint temp_level = speed - (level *speed / 100);
    en_dr_motor->flag_stop = 0;
    driver_6612_motor_move(speed, speed, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_BACK);
}

void driver_motor_stop(){
    // driver_6612_motor_move(25, 0, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_BACK);
    en_dr_motor->flag_stop += 1;
    // driver_6612_motor_move(0,0 , DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_FORVERD);
}
void stoooop(){
    driver_6612_motor_move(0, 0, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_FORVERD);
}