#ifndef __DRIVER_MOTOR_ENCIDER_H__
#define __DRIVER_MOTOR_ENCIDER_H__

#define DRIVER_MOTOR_FORVERD 1
#define DRIVER_MOTOR_BACK 0

#include "pico/stdlib.h"
// #include "motor_robot.h"
#include "Bobla_encoder_lib.h"
#include "Bobla_6612_motor_lib.h"



/// @brief init driver motor
/// @param motor_conf - struct motor config
/// @param enkoder_R - sruct encoder right conf
/// @param enkoder_L - struct encoder left conf
void driver_motor_init(motor_dc_pwm_6612_t* motor_conf, enkoder_t* enkoder_R, enkoder_t* enkoder_L);

/// @brief func for move forvard
/// @param speed speed move robot 
void driver_motor_forward(uint speed);

/// @brief func for left turn
/// @param level - lever turn
/// @param speed  - speed move robot
void driver_motor_forward_left(uint level, uint speed);


/// @brief func for right turn
/// @param level - lever turn
/// @param speed - speed move robot
void driver_motor_forward_right(uint level, uint speed);

/// @brief func for right turn on the spot
/// @param level - lever turn
/// @param speed - speed move robot
void driver_motor_forward_right_turn(uint level, uint speed);

/// @brief func for left turn on the spot
/// @param level - lever turn
/// @param speed - speed move robot
void driver_motor_forward_left_turn(uint level, uint speed);

/// @brief func for stop robot
void driver_motor_stop();

/// @brief 
/// @param len 
void driver_motor_len_move_to_line(int len);

// void stoooop();


#endif