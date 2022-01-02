cmake_minimum_required(VERSION 3.12)

file(TO_CMAKE_PATH "$ENV{PICO_SDK_PATH}" PICO_SDK_PATH_CMAKE)

# Pull in SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Project name : accessed as "Robokid_test" or ${PROJECT_NAME}
project(
        Robokid_test C CXX ASM
        )

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# create executable
add_executable(${PROJECT_NAME}
        Robokid_test.c
        OLED_128X64.c
        TMC7300.c
        ${PICO_SDK_PATH_CMAKE}/lib/tinyusb/src/tusb.c
        )

# include directories
#target_include_directories(${PROJECT_NAME} PUBLIC $ENV{PICO_SDK_PATH}/include)        
target_include_directories(${PROJECT_NAME} PUBLIC $ENV{PICO_SDK_PATH}/lib/tinyusb/src)        

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_spi tinyusb_board tinyusb_host)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
