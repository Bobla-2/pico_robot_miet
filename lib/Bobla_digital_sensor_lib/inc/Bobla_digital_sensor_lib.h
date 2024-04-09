#ifndef __BOBLA_BRAWLS_H__
#define __BOBLA_BRAWLS_H__

#include "pico/stdlib.h"
typedef enum {
    DIGITAL_DONE,
    DIGITAL_STOP,
    DIGITAL_MOVE_FORWORD,
    DIGITAL_MOVE_LEFT,
    DIGITAL_MOVE_RIGHT,
    DIGITAL_END,
}bobla_digital_stage_t;

typedef struct {
    uint* gpio;
    uint16_t len_gpio;
    uint state;   
    bobla_digital_stage_t stage_;
    bool inversion;
} bobla_digital_sensor_t;


/// @brief init sensor line
/// @param sensor_mas struct for sensor line: must have sensor_mode_t
void digital_sensor_init(bobla_digital_sensor_t* sensor_mas);

/// @brief func for read sensor digital in digital mode. Must be called frequently
void digital_sensor_read(bobla_digital_sensor_t* sensor_mas);

#endif
