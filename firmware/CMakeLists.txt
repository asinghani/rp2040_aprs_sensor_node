cmake_minimum_required(VERSION 3.15)

# Initialize Pico SDK
include(cmake/pico_sdk_import.cmake)
include(cmake/pico_extras_import.cmake)

project(aprs_sensor_node VERSION 1.0)
pico_sdk_init()

# Load the APRS TNC library
include(FetchContent)
FetchContent_Declare(aprs_pico
    GIT_REPOSITORY    "https://github.com/eleccoder/raspi-pico-aprs-tnc.git" 
    GIT_TAG main
    GIT_SHALLOW       ON
)

FetchContent_MakeAvailable(aprs_pico)
add_library(aprs_pico::aprs_pico ALIAS aprs_pico)

# Initialize the project build itself
set(TARGET_EXAMPLE_EXE_NAME aprs_sensor_node)
add_executable(aprs_sensor_node
    src/main.c
    src/dra818.c
    src/tmp102.c
)

pico_enable_stdio_usb(aprs_sensor_node 1)
pico_add_extra_outputs(aprs_sensor_node)

target_link_libraries(aprs_sensor_node
    aprs_pico
    pico_stdlib
    hardware_i2c
)

