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
    uint32_t state_d;
    uint16_t* state_a;   
    sensor_mode_t mode;
} sensor_t;



void sensor_init(sensor_t* sensor_mas);
void sensor_read_digital();

#endif
