cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Project name : accessed as "SSD1306_test" or ${PROJECT_NAME}
project(
        SSD1306_test 
        VERSION 1.0
        LANGUAGES C CXX ASM
        )

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# create executable
add_executable(${PROJECT_NAME}
        SSD1306_test.c
        OLED_128X64.c
        )

# include directories
#target_include_directories(${PROJECT_NAME} PUBLIC $ENV{PICO_SDK_PATH}/include)        

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_spi)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})
