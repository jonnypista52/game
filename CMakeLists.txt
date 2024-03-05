# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/botond/pico-sdk/pico/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(game C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(game
              errorCheck/basicError.cpp
              
              game.cpp
              controll/spi.cpp
              controll/spiPorts.cpp
              controll/SDCard.cpp

              pio/vga/vga.cpp

              input/Stick.cpp

              debug/printer.cpp
              debug/mix.cpp
              )

pico_set_program_name(game "game")
pico_set_program_version(game "0.1")

pico_enable_stdio_uart(game 0)
pico_enable_stdio_usb(game 1)

# Add the standard library to the build
target_link_libraries(game
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(game PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

#no malloc panic
target_compile_definitions(game PRIVATE PICO_MALLOC_PANIC=0)

pico_generate_pio_header(game ${CMAKE_CURRENT_LIST_DIR}/pio/hello.pio)
# Add any user requested libraries
target_link_libraries(game 
        hardware_spi
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        hardware_adc
        hardware_dma
        pico_multicore
        #       pico_sem
        pico_stdlib
        hardware_clocks
        hardware_pll
        )

pico_add_extra_outputs(game)

