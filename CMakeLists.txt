cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE cmake/toolchain-arm-gcc-cortex.cmake)

project(nrf52 C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# Disable existing Zephyr "flash" and "debug" targets to not interfere with custom targets defined in cmake/debug-probes/
execute_process(COMMAND git -C third_party/zephyr apply ../../dont-create-zephyr-flash-and-debug-targets.patch ERROR_QUIET)

set(ZEPHYR_TOOLCHAIN_VARIANT gnuarmemb)
get_filename_component(GNUARMEMB_TOOLCHAIN_PATH ${CMAKE_C_COMPILER}/../.. ABSOLUTE)
set(BOARD nrf52dk_nrf52832)
set(ZEPHYR_MODULES ${CMAKE_CURRENT_LIST_DIR}/third_party/cmsis ${CMAKE_CURRENT_LIST_DIR}/third_party/hal_nordic ${CMAKE_CURRENT_LIST_DIR}/third_party/mcuboot ${CMAKE_CURRENT_LIST_DIR}/third_party/nrf ${CMAKE_CURRENT_LIST_DIR}/third_party/sdk-nrfxlib ${CMAKE_CURRENT_LIST_DIR}/third_party/segger)
find_package(Zephyr REQUIRED HINTS ${CMAKE_CURRENT_LIST_DIR}/third_party/zephyr)

target_sources(app PRIVATE main.cpp)

# Add targets for flashing, erasing, resetting and debugging
set(JLINK_PARAMS -device nRF52832_xxAA -if SWD)
include(cmake/debug-probes/jlink.cmake)
