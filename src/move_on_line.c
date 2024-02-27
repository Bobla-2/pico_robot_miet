#include "move_on_line.h"
#include "pico/stdlib.h"
#include "motor_robot.h"
#include "enkoder.h"
#include "sensor.h"

sensor_t *en_sensor_line;
bool invers_senser;
uint en_speed;
uint16_t sens_level;

void move_line_init(sensor_t *sensor_line) { 
    en_sensor_line = sensor_line;
    en_speed = 40;
    sens_level = 1000;
}

void move_line_deinit(void) { 
    en_sensor_line = NULL;
}

void move_line_hangler_sensor (uint *buf_state);

void move_line_core(void) {
    uint buf_state;
    move_line_hangler_sensor(&buf_state);
    if (en_sensor_line->len == 3){
        switch (buf_state){
        case MOVE_LINE_3_STOP:
            motor_robot_stop();
            break;
        case MOVE_LINE_3_FORWARD_LEFT:
            motor_robot_forward_turn_enkoder(-1, en_speed, 30, true);
            break;
        case MOVE_LINE_3_FORWARD_RIGHT:
            motor_robot_forward_turn_enkoder(1, en_speed, 30, true);
            break;
        default:
            break;
        }
    
    } else {
        print("error: MOVE_LINE en_sensor_line->len");
    }
}

void move_line_hangler_sensor (uint *buf_state){
    if (en_sensor_line->mode == ANALOG_sensor){
        bool temp;
        for (uint i = 0; i < en_sensor_line->len; i++){
            temp = (en_sensor_line->state_a[i] > sens_level) ? true : false;
            *buf_state |= temp << i;
        }
    } else {
        *buf_state = en_sensor_line->state_d;
    }
}

