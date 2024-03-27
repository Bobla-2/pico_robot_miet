#include "move_on_line.h"
#include "pico/stdlib.h"
// #include "motor_robot.h"
#include "Bobla_encoder_lib.h"

// #include "Bobla_sensor_line_lib.h"
#include "driver_motor_encoder.h"

sensor_t *en_sensor_line;
bool invers_senser;
uint en_speed;
uint16_t sens_level;

void move_line_init(sensor_t *sensor_line) { 
    en_sensor_line = sensor_line;
    en_speed = 20;
    sens_level = 1700;
}

void move_line_deinit(void) { 
    en_sensor_line = NULL;
}

void move_line_core(void) {
    uint buf_state = 0;
    
    if (en_sensor_line->len == 3){
        uint temp;
        for (uint i = 0; i < en_sensor_line->len; i++){
            temp = (en_sensor_line->state_a[i] > sens_level) ? 1 : 0;
            buf_state |= (temp << i);
            // printf("line55 =%d/\r\n",buf_state);
        }


        switch (buf_state){
        case MOVE_LINE_3_STOP:
            driver_motor_stop();
            // motor_robot_stop();
            break;
        case MOVE_LINE_3_FORWARD_LEFT:
            driver_motor_forward_left(50,20);
            // motor_robot_forward_turn_enkoder(-1, en_speed, 100, true);
            break;
        case MOVE_LINE_3_FORWARD_RIGHT:
            driver_motor_forward_right(50,20);
            // motor_robot_forward_turn_enkoder(1, en_speed, 100, true);
            break;
        case MOVE_LINE_3_FORWARD:
            driver_motor_forward(20);
            // motor_robot_forward_turn_enkoder(1, en_speed, 100, true);
            break;
        case MOVE_LINE_3_FORWARD_LEFT_TURN:
            driver_motor_forward_right_turn(100,20);
            break;
        case MOVE_LINE_3_FORWARD_RIGHT_TURN:
            driver_motor_forward_left_turn(100,20);
            break;
        
        default:
            break;
        }
    }else{
        printf("ERROR count sensor line (move on line)");
    }
}

void move_brawls_core(bobla_brawls_sensor_t* sesnsor){


}



