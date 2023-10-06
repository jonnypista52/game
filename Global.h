#ifndef Global_h
#define Global_h

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

//*TestProbes
#define SD_SCK_test 19
#define SD_MOSI_test 18
#define SD_MISO_test 17
#define SD_CS_test 16


#endif