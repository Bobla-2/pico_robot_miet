#ifndef __BOBLA_BRAWLS_H__
#define __BOBLA_BRAWLS_H__

#include "pico/stdlib.h"
typedef enum {
    BRAWELS_DONE,
    BRAWELS_STOP,
    BRAWELS_MOVE_FORWORD,
    BRAWELS_MOVE_LEFT,
    BRAWELS_MOVE_RIGHT,
}bobla_brawls_stage_t;

typedef struct {
    uint* gpio;
    uint16_t len_gpio;
    uint state;   
    bobla_brawls_stage_t stage_;
} bobla_brawls_sensor_t;


/// @brief init sensor line
/// @param sensor_mas struct for sensor line: must have sensor_mode_t
void brawls_sensor_init(bobla_brawls_sensor_t* sensor_mas);

/// @brief func for read sensor brawls in digital mode. Must be called frequently
void brawls_sensor_read();

#endif
