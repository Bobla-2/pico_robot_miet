#ifndef __BOBLA_6LIB_H__
#define __BOBLA_6LIB_H__

#include "pico/stdlib.h"
#include "pico/types.h"
// typedef enum {
//     DIGITAL_DONE,
//     DIGITAL_STOP,
//     DIGITAL_MOVE_FORWORD,
//     DIGITAL_MOVE_LEFT,
//     DIGITAL_MOVE_RIGHT,
//     DIGITAL_END,
// }bobla_6lib_stage_t;

typedef struct {
    volatile uint gpio_echo;
    volatile uint gpio_trig;
    volatile uint len;
    volatile uint state;
    volatile uint time_stamp;
    volatile uint old_time_stamp;

    // bobla_6lib_stage_t stage_;
} bobla_6lib_sensor_t;


/// @brief init sensor line
/// @param sensor_mas struct for sensor line: must have sensor_mode_t
void l6_sensor_init(bobla_6lib_sensor_t* sensor);

/// @brief func for read sensor digital in digital mode. Must be called frequently
void l6_sensor_read();

#endif
