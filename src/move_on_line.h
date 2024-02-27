#ifndef __MOVE_ON_LINE_H__
#define __MOVE_ON_LINE_H__

#include "pico/stdlib.h"

#include "sensor.h"
#include "motor_robot.h"
/// @brief init systen move on line
/// @param sensor_line 
/// @param motor 
void move_line_init(sensor_t *sensor_line, motor_dc_pwm_6612_t *motor);

/// @brief core for work sistem move on line // needs to be called 1000 times/sek.
int move_line_core(void);

/// @brief deinit systen move on line
void move_line_deinit(void);

#endif
