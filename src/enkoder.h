#ifndef __ENKODER_H__
#define __ENKODER_H__
#include "pico/stdlib.h"


typedef struct {
    uint gpio;
    bool state;
    int count;
    
} enkoder_t;

void enkoder_init(enkoder_t* enkoder_L, enkoder_t* enkoder_R);
void enkoder_init_old(enkoder_t* enkoder_L, enkoder_t* enkoder_R);
void enkoder_read();

#endif