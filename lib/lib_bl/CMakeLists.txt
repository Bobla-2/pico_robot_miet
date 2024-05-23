cmake_minimum_required(VERSION 3.12)

# Debug message
message("Entering ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")

set(NAME_LIB lib_bl)

set(NAME_SOURCES_C lib_bl.c)

# Register core library
add_library(${NAME_LIB} INTERFACE)
target_sources(${NAME_LIB} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/${NAME_SOURCES_C})
target_include_directories(${NAME_LIB} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/inc)
target_link_libraries(${NAME_LIB} INTERFACE pico_stdlib
		hardware_gpio
		hardware_irq
        hardware_uart)

# Register other modules

# Debug message
message("Exiting ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt")
