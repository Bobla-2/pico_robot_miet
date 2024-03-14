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
    // printf("line11----------- =%zu/\r\n",buf_state);
    //printf("line111 =%d/\r\n",buf_state);

    // move_line_hangler_sensor(&buf_state);
    // printf("line222 =%d/\r\n",buf_state);
    //if (en_sensor_line->len == 3){
        uint temp;
        // printf("line111 =%d/\r\n",buf_state);
        // buf_state = 0;
        for (uint i = 0; i < en_sensor_line->len; i++){
            temp = (en_sensor_line->state_a[i] > sens_level) ? 1 : 0;
            buf_state |= (temp << i);
            // printf("line55 =%d/\r\n",buf_state);
            // *buf_state = 1;
        }



        
        // printf("line55----------- =%zu/\r\n",buf_state);
        // buf_state = 2;
        // printf("line55----------- =%zu/\r\n",buf_state);
        // driver_motor_forward(40);
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
        
    
    // } else {
    //     // print("error: MOVE_LINE en_sensor_line->len");
    // }
}

// void move_line_hangler_sensor (uint *buf_state){
//     if (en_sensor_line->mode == ANALOG_sensor){
//         uint temp;
//         // printf("line111 =%d/\r\n",*buf_state);
//         for (uint i = 0; i < en_sensor_line->len; i++){
//             // printf("line55 =%d/\r\n",*buf_state);
//             temp = (en_sensor_line->state_a[i] < sens_level) ? 1 : 0;
//             *buf_state |= (temp << i);
//             // *buf_state = 1;
//         }
//     } else {
//         *buf_state = en_sensor_line->state_d;
//     }
// }

