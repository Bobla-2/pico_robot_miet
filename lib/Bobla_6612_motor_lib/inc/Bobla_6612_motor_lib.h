#ifndef __MOTOR_6612_H__
#define __MOTOR_6612_H__
#include "pico/stdlib.h"

#define ROBOT_CCW 0
#define ROBOT_CW 1
typedef enum {
    CCW,
    CW,
} motor_direct_t;

typedef enum {
    FRONT,
    REAR,
} motor_direct_6612_t;

/// @brief enum status for mashine state
typedef enum {
    NONE_,
    FORWARD,
    FORWARD_TURN,
    TURN_SPOT_L,
    TURN_SPOT_R,
    TURN_L,
    TURN_R,
    BACK,
    STOP_,
} motor_robot_status_t;


/// @brief struct for work driver 6612
typedef struct {
    int k_L;
    int k_R;
    int k2_L;
    int k2_R;
    uint gpio_Lin1;
    uint gpio_Lin2;
    uint gpio_Rin1;
    uint gpio_Rin2;
    uint gpio_Lpwm;
    uint gpio_Rpwm;
    uint gpio_stby;
    uint16_t speed;
    uint16_t speed_req;
    motor_direct_6612_t direct;
    motor_robot_status_t status_dc; 
    uint32_t flag_stop;
    bool flag_enable_irq;
}motor_dc_pwm_6612_t;

/// @brief func for 
/// @param motor_robot srtuct motor 
void driver_motor_6612_robot_init(motor_dc_pwm_6612_t* motor_robot);

/// @brief func for move motors
/// @param speed_R speed right motor 
/// @param speed_L speed left motor
/// @param DIR_R direction right motor
/// @param DIR_L direction left motor (FORVERD=1/BACK=0)
void driver_6612_motor_move(uint speed_R, uint speed_L, int DIR_R, int DIR_L);

#endif