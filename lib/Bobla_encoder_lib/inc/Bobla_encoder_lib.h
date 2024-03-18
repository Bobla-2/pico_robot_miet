#ifndef __ENKODER_H__
#define __ENKODER_H__
#include "pico/stdlib.h"

/// @brief struct Encoder
typedef struct {
    uint gpio;
    bool state;
    volatile int count;
    volatile uint32_t time_old_stamp;
    
} enkoder_t;

/// @brief Encoder library initialization function using interrupts
/// @param enkoder_L struct left Encoder
/// @param enkoder_R struct right Encoder
void enkoder_init_with_irq(enkoder_t* enkoder_L, enkoder_t* enkoder_R);

/// @brief Encoder library initialization function NO interrupts
/// @param enkoder_L struct left Encoder
/// @param enkoder_R struct right Encoder
void enkoder_init_NO_irq(enkoder_t* enkoder_L, enkoder_t* enkoder_R);

/// @brief Function for operation of encoders without interruption, must be called frequently
void enkoder_core_no_irq();

#endif