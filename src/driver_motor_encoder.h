#ifndef __DRIVER_MOTOR_ENCIDER_H__
#define __DRIVER_MOTOR_ENCIDER_H__

#include "pico/stdlib.h"
#include "motor_robot.h"
#include "enkoder.h"


/// @brief init
/// @param motor_conf 
/// @param enkoder_R 
/// @param enkoder_L 
void driver_motor_init(motor_dc_pwm_6612_t* motor_conf, enkoder_t* enkoder_R, enkoder_t* enkoder_L);
void driver_motor_forward(uint speed);

void driver_motor_forward_left(uint level, uint speed);
void driver_motor_forward_right(uint level, uint speed);
void driver_motor_stop();

#endif