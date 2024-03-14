#ifndef __MOVE_ON_LINE_H__
#define __MOVE_ON_LINE_H__

#include "pico/stdlib.h"
#include "Bobla_sensor_line_lib.h"
#include "motor_robot.h"

enum move_line_t {
    MOVE_LINE_3_NONE = 0,
    MOVE_LINE_3_FORWARD_LEFT = 1,
    MOVE_LINE_3_FORWARD = 2,
    MOVE_LINE_3_FORWARD_LEFT_TURN = 3,
    MOVE_LINE_3_FORWARD_RIGHT = 4,
    MOVE_LINE_3_FORWARD_RIGHT_TURN = 6,
    MOVE_LINE_3_STOP = 7,
};




/// @brief init systen move on line
/// @param sensor_line 
/// @param motor 
void move_line_init(sensor_t *sensor_line);

/// @brief core for work sistem move on line // needs to be called 1000 times/sek.
void move_line_core(void);

/// @brief deinit systen move on line
void move_line_deinit(void);

#endif
