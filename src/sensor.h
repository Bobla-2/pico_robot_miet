#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "pico/stdlib.h"

typedef struct {
    uint* gpio;
    uint8_t len;
    uint32_t state;
} sensor_t;


void sensor_init(sensor_t* sensor_mas);
void sensor_read(sensor_t* sensor_mas);

#endif
