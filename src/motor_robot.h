#ifndef __MOTOR_ROBOT_H__
#define __MOTOR_ROBOT_H__

// #include "motor_dc_pwm.h"
#include "pico/stdlib.h"
#include "enkoder.h"
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

typedef enum {
    NONE,
    STOP,
    BRAKE,
    START,
} motor_dc_status_t;
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

// typedef struct {
//     uint gpioA;
//     uint gpioB;
//     uint16_t speed;
//     uint16_t speed_req;
//     motor_direct_t direct;
//     // uint ID;
//     motor_dc_status_t status_dc;
      
// }motor_dc_pwm_t;

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
    // uint ID;
    motor_robot_status_t status_dc;
      
}motor_dc_pwm_6612_t;

// typedef struct {
//     motor_dc_pwm_t * motor_L;
//     motor_dc_pwm_t * motor_R;
//     motor_robot_status_t status_dc;
// } motor_robot_t;


// void motor_robot_init(motor_robot_t* motor_robot);
// void motor_robot_forward(motor_robot_t* motor_robot, uint16_t speed);
// void motor_robot_forward_turn(motor_robot_t* motor_robot, uint DIR, uint engle);
// void motor_robot_turn_spot(motor_robot_t* motor_robot, uint DIR);
// void motor_robot_turn(motor_robot_t* motor_robot, uint DIR);
// void motor_robot_back(motor_robot_t* motor_robot);
// void motor_robot_stop(motor_robot_t* motor_robot);
// void motor_init(motor_dc_pwm_t* motor);
// void motor_start(motor_dc_pwm_t* motor);
// void motor_stop(motor_dc_pwm_t* motor);
void motor_6612_robot_init(motor_dc_pwm_6612_t* motor_robot);
void motor_6612_robot_forward(motor_dc_pwm_6612_t* motor_robot, uint16_t speed);
// void motor_6612_robot_forward_turn(motor_dc_pwm_6612_t* motor_robot, uint DIR, uint engle);
void motor_6612_robot_turn_spot(motor_dc_pwm_6612_t* motor_robot, uint DIR);
void motor_6612_robot_turn(motor_dc_pwm_6612_t* motor_robot, uint DIR);
void motor_6612_robot_back(motor_dc_pwm_6612_t* motor_robot);
void motor_6612_robot_stop(motor_dc_pwm_6612_t* motor_robot);

void motor_6612_robot_forward_encoder(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L, uint len, uint speed);
// void motor_6612_robot_forward_turn_encoder(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L, uint engle, uint speed);
void motor_6612_robot_forward_turn_enkoder(motor_dc_pwm_6612_t* motor_robot, enkoder_t* enkoder_R, enkoder_t* enkoder_L, int engle, uint speed, int radius);


#endif