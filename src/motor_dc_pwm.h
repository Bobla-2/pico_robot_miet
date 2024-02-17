#ifndef __MOTOR_DC_PWM_H__
#define __MOTOR_DC_PWM_H__

#include "pico/stdlib.h"
typedef enum {
    CCW,
    CW,
} motor_direct_t;

typedef enum {
    NONE,
    STOP,
    BRAKE,
    START,
} motor_status_t;

typedef struct {
    uint8_t gpioA;
    uint8_t gpioB;
    int speed;
    int speed_req;
    motor_direct_t direct;
    uint ID;
    motor_status_t status;
      
}motor_dc_pwm_t;

void motor_init(motor_dc_pwm_t* motor);
void motor_start(motor_dc_pwm_t* motor);
void motor_stop(motor_dc_pwm_t* motor);

#endif