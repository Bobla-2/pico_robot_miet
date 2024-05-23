#ifndef __MOVE_ON_LINE_H__
#define __MOVE_ON_LINE_H__

#include "pico/stdlib.h"
#include "Bobla_sensor_line_lib.h"
#include "Bobla_digital_sensor_lib.h"
#include "Bobla_6lib_sensor_lib.h"
// #include "motor_robot.h"

enum move_line_t {
    MOVE_LINE_3_NONE = 0,
    MOVE_LINE_3_FORWARD_LEFT = 1,
    MOVE_LINE_3_FORWARD = 2,
    MOVE_LINE_3_FORWARD_LEFT_TURN = 3,
    MOVE_LINE_3_FORWARD_RIGHT = 4,
    MOVE_LINE_3_FORWARD_RIGHT_TURN = 6,
    MOVE_LINE_3_STOP = 7,
};

typedef enum {
    MOVE_LINE_NONE,
    MOVE_LINE_FORWARD,
    MOVE_LINE_RIDHT,
    MOVE_LINE_LEFT,
    MOVE_LINE_RIDHT_LEFT,
    MOVE_LINE_LEFT_FORWARD,
    MOVE_LINE_RIDHT_FORWARD,
    MOVE_LINE_RIDHT_LEFT_FORWARD,
} move_line_type_line_t;




/// @brief init systen move on line
/// @param sensor_line 
/// @param motor 
void move_line_init(sensor_t *sensor_line);

/// @brief core for work sistem move on line // needs to be called 1000 times/sek.
void move_line_core(void);

/// @brief deinit systen move on line
void move_line_deinit(void);

void move_digital_core(bobla_digital_sensor_t* sesnsor);

void move_into_cyrcol();
void move_to_bunk_core(bobla_digital_sensor_t* digital_sensor);
int move_on_line_v2(bobla_digital_sensor_t* sensor_line);
void move_to_l6_core(bobla_6lib_sensor_t* sensor);
void move_to_hui(uint8_t seor);

#endif
