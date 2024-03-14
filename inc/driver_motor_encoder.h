#ifndef __DRIVER_MOTOR_ENCIDER_H__
#define __DRIVER_MOTOR_ENCIDER_H__

#define DRIVER_MOTOR_FORVERD 1
#define DRIVER_MOTOR_BACK 0

#include "pico/stdlib.h"
#include "motor_robot.h"
#include "Bobla_encoder_lib.h"



/// @brief init
/// @param motor_conf 
/// @param enkoder_R 
/// @param enkoder_L 
void driver_motor_init(motor_dc_pwm_6612_t* motor_conf, enkoder_t* enkoder_R, enkoder_t* enkoder_L);
void driver_motor_forward(uint speed);

void driver_motor_forward_left(uint level, uint speed);
void driver_motor_forward_right(uint level, uint speed);
void driver_motor_forward_right_turn(uint level, uint speed);
void driver_motor_forward_left_turn(uint level, uint speed);
void driver_motor_stop();
void stoooop();

#endif