#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "pico/stdlib.h"

typedef enum {
    DIGITAL_sensor,
    ANALOG_sensor,
} sensor_mode_t;

typedef struct {
    uint* gpio;
    uint16_t len;
    uint state_d;
    uint16_t* state_a;   
    sensor_mode_t mode;
} sensor_t;


/// @brief init sensor line
/// @param sensor_mas struct for sensor line: must have sensor_mode_t
void sensor_init(sensor_t* sensor_mas);

/// @brief func for read sensor line in digital mode. Must be called frequently
void sensor_read_digital();

#endif
