#include "move_on_line.h"
#include "pico/stdlib.h"
// #include "motor_robot.h"
#include "Bobla_encoder_lib.h"

#include "Bobla_digital_sensor_lib.h"
#include "driver_motor_encoder.h"
#include "pico/types.h"
#include <stdint.h>

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
    static uint timer123 = 0;
    static uint timeflag = 0;
    if (en_sensor_line->len == 3){
        uint temp;
        for (uint i = 0; i < en_sensor_line->len; i++){
            temp = (en_sensor_line->state_a[i] > 1000) ? 0 : 1;
            buf_state |= (temp << i);
        }

        printf("line55 =%d/\r\n",buf_state);
        if (timeflag == 0){
            if (buf_state != 0){
                driver_motor_forward_left_turn(100, 25);
                timeflag = 1;
            } else {
                driver_motor_forward(35);
                
            }

        } else {
            timer123 += 1;
            if (timer123 == 10){
                timer123 = 0;
                timeflag = 0;
            }
        }
        
    
    }
}

void move_to_bunk_core(bobla_digital_sensor_t* digital_sensor){
    static uint timehui = 0;
    if (digital_sensor->state == 2 && digital_sensor->stage_ == 0){
        driver_6612_motor_move(25, 25, DRIVER_MOTOR_BACK, DRIVER_MOTOR_FORVERD);
        digital_sensor->stage_ = 1;

    } else if (digital_sensor->state == 1 && digital_sensor->stage_ == 1){
        driver_motor_forward(20);
        digital_sensor->stage_ = DIGITAL_END;
    }
    if (digital_sensor->stage_ == 1){
        timehui += 1;
        if (timehui == 120){
            timehui = 0;
            driver_motor_forward(20);
            digital_sensor->stage_ = DIGITAL_END;
        }
    }
}

int countOnes(int num) {
    int count = 0;
    while (num != 0) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}
int move_on_line_read_turn(bobla_digital_sensor_t* sensor_line){
    static uint stage_read_trase = 0;
    static move_line_type_line_t temp_type_line = 0;
    switch (stage_read_trase){
        case 0:
        printf("temp_type_line22 = %d;;;sens=%d\n", temp_type_line, sensor_line->state);
            if (driver_motor_len_move_to_line(13) == 1) stage_read_trase = 1;

            if (sensor_line->state == 31 && temp_type_line != MOVE_LINE_RIDHT_LEFT_FORWARD){
                temp_type_line = MOVE_LINE_RIDHT_LEFT;
            } 

            if (temp_type_line == 0) {
                if (sensor_line->state == 28 || sensor_line->state == 24) {
                    temp_type_line = MOVE_LINE_LEFT;
                } else if (sensor_line->state == 3 || sensor_line->state == 7){
                    temp_type_line = MOVE_LINE_RIDHT;
                }
            }
            printf("temp_type_line33 = %d\n", temp_type_line);
            break;
        case 1:
        
            printf("temp_type 344 = %d, sensor_line->state : %d\n", temp_type_line, sensor_line->state);

            if(sensor_line->state == 4){
                if(temp_type_line == MOVE_LINE_RIDHT_LEFT) temp_type_line = MOVE_LINE_RIDHT_LEFT_FORWARD;
                if(temp_type_line == MOVE_LINE_LEFT) temp_type_line = MOVE_LINE_LEFT_FORWARD;
                if(temp_type_line == MOVE_LINE_RIDHT) temp_type_line = MOVE_LINE_RIDHT_FORWARD;
            }
            printf("temp_type444 = %d\n", temp_type_line);
            stage_read_trase = 2;
            break;
        case 2:
            
            printf("temp_type98776_line = %d\n", temp_type_line);
            int temp = temp_type_line;
            temp_type_line = 0;
            stage_read_trase = 0;
            return temp;
            
            break;
        
        default:
            break;
    
    }
    return 0;
} 

int move_on_line_choice_turn(int type_line){
    uint16_t tepm_random = en_sensor_line->state_a[1];
    uint tepm_random__ = (tepm_random << (32 - type_line));
    return countOnes(tepm_random__);
}

int move_on_line_v2(bobla_digital_sensor_t* sensor_line){
    static uint flag_mod_move = 0;
    static uint flag_mod_move_addad = 0;
    
        printf("line = %d\n", sensor_line->state);
        //if (countOnes(sensor_line->state) <= 2){
        if (flag_mod_move == 0){  
            if (flag_mod_move_addad == 1){
                    if (sensor_line->state == 4){
                        flag_mod_move_addad = 0;
                       
                    } else {
                         return 0;
                    }
                }
            switch (sensor_line->state){
                case 2:
                    driver_motor_forward_left(50,20);
                    break;
                case 6:
                    driver_motor_forward_left(30,20);
                    break;
                case 4:
                    driver_motor_forward(20);
                    break;
                case 12:
                    driver_motor_forward_right(30,20);
                    break;
                case 8:
                    driver_motor_forward_right(50,20);
                    break;
                
                default:
                
                    flag_mod_move = 1;
                    break;
            }
        } else {
            flag_mod_move_addad = 1;
            int static temp_type_line = 0; 
            uint static state_turn_ = 0;
            uint static turn__ = 0;
            
            switch (state_turn_) {
                case 0:
                    temp_type_line = move_on_line_read_turn(sensor_line);
                    printf("temp_type_line() = %d\n", temp_type_line);
                    if (temp_type_line == MOVE_LINE_RIDHT){
                        printf("MOVE_LINE_Right\n");
                        turn__ = temp_type_line;
                        state_turn_ = 2;
                    }
                    else if (temp_type_line == MOVE_LINE_LEFT){
                        printf("MOVE_LINE_LEFT\n");
                        turn__ = temp_type_line;
                        state_turn_ = 2;  
                    }
                    else if (temp_type_line != 0) state_turn_ = 1;
                    break;        
                    printf("temp_type_line(1) = %d\n", state_turn_);
                
                case 1:
                // тут я остановился
                // надо проверить move_on_line_choice_turn
                // функции написать поворот 
                    printf("temp_type_case 1 = %d\n", temp_type_line);
                    // turn__ = move_on_line_choice_turn(temp_type_line);
                    turn__ = temp_type_line;
                    state_turn_ = 2;    
                    printf("turn__ 1 = %d\n", turn__);
                    break; 
                case 2:
                    switch (turn__) {
                        case MOVE_LINE_LEFT:
                            if (driver_motor_len_move_to_right(36) == 1) turn__ = 10;
                            printf("driver_motor_len_move_to_left RIGHT = %d\n", turn__);
                            break;
                        case MOVE_LINE_RIDHT:
                            printf("driver_motor_len_move_to_left LEFT = %d\n", turn__);
                            if (driver_motor_len_move_to_left(36) == 1) turn__ = 10;
                            break;
                        case MOVE_LINE_RIDHT_LEFT:
                            if (driver_motor_len_move_to_left(36) == 1) turn__ = 10;
                            printf("driver_motor_len_move_to_left = %d\n", turn__);
                            
                            break;
                        case MOVE_LINE_RIDHT_LEFT_FORWARD:
                        if (driver_motor_len_move_to_right(36) == 1) turn__ = 10;
                            printf("driver_motor_len_move_to_r = %d\n", turn__);
                            break;
                        case 10:
                            flag_mod_move = 0;
                            state_turn_ = 0;
                            turn__ = 0;
                            break;
                        default:
                            break;


                    
                    }
                    
            }
        } 


    return 0;
}

void move_to_l6_core(bobla_6lib_sensor_t* sensor){
    // static uint timehui = 0;
    static uint turn_e_ = 0;
    
    switch (turn_e_) {
        case 0:
            driver_motor_forward(20);
            if (sensor->len < 20) turn_e_ = 1;
            break;
        case 1:
            if (driver_motor_len_move_to_right(30) == 1) turn_e_ = 2;
            break;
        case 2:
            driver_motor_forward(20);
            if (sensor->len < 20) turn_e_ = 3;
            break;
        case 3:
            if (driver_motor_len_move_to_left(30) == 1) turn_e_ = 0;

            break;
    } 
}
void move_to_hui(uint8_t seor){
    // static uint timehui = 0;
    if (seor == 53) driver_motor_forward(20);
    if (seor == 52) driver_motor_stop();
     
}

