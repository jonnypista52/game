#ifndef Global_h
#define Global_h

#include <pico/stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/divider.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"

#include "./debug/printer.h"

//* power level
#define HIGH 1
#define LOW 0

//* DAC pins
#define SD_SPI_CHANNEL 0
#define SD_FREQ 400000
#define SD_SCK 2
#define SD_MOSI 3
#define SD_MISO 4
#define SD_CS 5

//*VGA signals
#define HSYNC 6
#define VSYNC 7
#define VIDEOR0 8

#define BUFFER_LINE_SIZE 96
#define NROFBGSPRITES 8
#define BGSPRITES_SIZE 32
#define NUM_PIXELS_INLINE 640
#define NUM_LINE_SCREEN 480

#define MAPHEIGTH NUM_LINE_SCREEN/BGSPRITES_SIZE
#define MAPLENGHT NUM_PIXELS_INLINE/BGSPRITES_SIZE

#endif