#include "move_in_line.h"
#include "pico/stdlib.h"
#include "motor_robot.h"
#include "enkoder.h"
#include "sensor.h"

motor_dc_pwm_6612_t *en_motor;
sensor_t *en_sensor_line;
bool invers_senser;


void move_line_init(sensor_t *sensor_line, motor_dc_pwm_6612_t *motor) { 
    en_motor = motor;
    en_sensor_lone = sensor_line;
}

void move_line_deinit(void) { 
    en_motor = NONE;
    en_sensor_line = NONE;
}

void move_line_deinit(bool ) { 
    en_motor = NONE;
    en_sensor_line = NONE;
}
uint move_line_hangler_sensor (void);

void move_line_core(void) {
    switch (move_line_hangler_sensor())
    {
    case MOVE_FORWARD:
        /* code */
        break;
    
    default MOVE_STOP:
        break;
    }

        
}

uint move_line_hangler_sensor (void){
    bool buf_state[en_sensor_line->len];
    if (en_sensor_line->mode == ANALOG_sensor){
        
        // for (int i = 0; i < en_sensor_line->len; i++){

        //     en_sensor_line->state_a[i]
        // }
        if (en_sensor_line->state_a[1] > en_sensor_line->state_a[0] && en_sensor_line->state_a[1] > en_sensor_line->state_a[2]){
            if (en_sensor_line->state_a[0] > en_sensor_line->state_a[2]){
                motor_6612_robot_forward_turn_enkoder(en_motor, )
        }

    } else {
        for (uint32_t i = 0; i < en_sensor_line->len; i++){
            buf_state[i] = en_sensor_line->state_d & (1 << i);
        }
    }



}