cmake_minimum_required(VERSION 3.12)

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/build)

include(pico_sdk_import.cmake)
project(test C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )

add_executable(${CMAKE_PROJECT_NAME} src/main.c)

add_subdirectory(lib/Bobla_6612_motor_lib)
add_subdirectory(lib/Bobla_encoder_lib)
add_subdirectory(lib/Bobla_sensor_line_lib)
add_subdirectory(lib/Bobla_digital_sensor_lib)
add_subdirectory(lib/Bobla_6lib_sensor_lib)
add_subdirectory(lib/lib_bl)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC
                ${CMAKE_CURRENT_SOURCE_DIR}/src/driver_motor_encoder.c
                ${CMAKE_CURRENT_SOURCE_DIR}/src/move_on_line.c)

target_link_libraries(${CMAKE_PROJECT_NAME} 
                pico_stdlib
                hardware_uart
                hardware_pwm
                hardware_irq
                hardware_adc 
                hardware_watchdog
                Bobla_encoder_lib
                Bobla_sensor_line_lib
                Bobla_6612_motor_lib
                Bobla_digital_sensor_lib
                Bobla_6lib_sensor_lib
                lib_bl
                )
                
include_directories(inc)

# pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
# pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
