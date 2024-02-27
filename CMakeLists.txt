cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
project(test C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
        
add_executable(test src/main.c)

target_link_libraries(test 
                    pico_stdlib
                    hardware_pwm
                    hardware_irq
                    hardware_adc 
                    hardware_watchdog
                   
                    )
target_sources(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/sensor.c
                # ${CMAKE_CURRENT_SOURCE_DIR}/src/motor_dc_pwm.c)
                ${CMAKE_CURRENT_SOURCE_DIR}/src/enkoder.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/motor_robot.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/move_on_line.c)

# pico_enable_stdio_usb(test 1)
# pico_enable_stdio_uart(test 0)
pico_add_extra_outputs(test)
