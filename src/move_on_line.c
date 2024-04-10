#include "move_on_line.h"
#include "pico/stdlib.h"
// #include "motor_robot.h"
#include "Bobla_encoder_lib.h"

#include "Bobla_digital_sensor_lib.h"
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

void move_digital_core(bobla_digital_sensor_t* digital_sensor){

    if (digital_sensor->state == 1 && digital_sensor->stage_ == DIGITAL_DONE){
        //stoooop();
        digital_sensor->stage_ = 1;
        driver_6612_motor_move(25, 15, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_BACK);

    } else if (digital_sensor->state == 2 && digital_sensor->stage_ == 1){
        driver_6612_motor_move(15, 30, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_FORVERD);
        digital_sensor->stage_ = 2;

    } else if (digital_sensor->stage_ == 2){
        digital_sensor->stage_ = DIGITAL_END;
    }
}

void move_safe_for_drop_table(bobla_digital_sensor_t* drop_sensor){
    if (drop_sensor->state != 0){
        driver_motor_len_move_to_line(-20);
        driver_6612_motor_move(20, 20, DRIVER_MOTOR_FORVERD, DRIVER_MOTOR_BACK);
        sleep_ms(500);
    }
}

void move_into_cyrcol(){
    uint buf_state = 0;
    
    if (en_sensor_line->len == 3){
        uint temp;
        for (uint i = 0; i < en_sensor_line->len; i++){
            temp = (en_sensor_line->state_a[i] > sens_level) ? 0 : 1;
            buf_state |= (temp << i);
            // printf("line55 =%d/\r\n",buf_state);
        }


        if (buf_state != 0){
            driver_motor_forward_left_turn(100, 25);
        } else {
            driver_motor_forward(25);
            sleep_ms(300);
        }
        
    
    }
}
