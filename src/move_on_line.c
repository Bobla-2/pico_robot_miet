#include "move_on_line.h"
#include "pico/stdlib.h"
#include "motor_robot.h"
#include "enkoder.h"
#include "sensor.h"

sensor_t *en_sensor_line;
bool invers_senser;
uint en_speed;

void move_line_init(sensor_t *sensor_line) { 
    en_sensor_line = sensor_line;
    en_speed 40;
}

void move_line_deinit(void) { 
    en_sensor_line = NULL;
}

move_line_t move_line_hangler_sensor (void);

void move_line_core(void) {
    move_line_hangler_sensor();
     
}

move_line_t move_line_hangler_sensor (void){
    bool buf_state[en_sensor_line->len];

    if (en_sensor_line->mode == ANALOG_sensor){
        
        // for (int i = 0; i < en_sensor_line->len; i++){/

        //     en_sensor_line->state_a[i]
        // }
        if (en_sensor_line->state_a[1] > en_sensor_line->state_a[0] && en_sensor_line->state_a[1] > en_sensor_line->state_a[2]){
            if (en_sensor_line->state_a[0] < en_sensor_line->state_a[2]){
                motor_robot_forward_turn_enkoder(
                    1,
                    en_speed,
                    100/en_sensor_line->state_a[2]-en_sensor_line->state_a[0],
                    true
                );
            } else {
                motor_robot_forward_turn_enkoder(
                    -1, 
                    en_speed, 
                    100/en_sensor_line->state_a[0]-en_sensor_line->state_a[1], 
                    true
                );
            }

        } else {
            for (uint32_t i = 0; i < en_sensor_line->len; i++){
                buf_state[i] = en_sensor_line->state_d & (1 << i);
            }
        }

    }

}