#pragma once

#ifndef TESTING
#include "Global.h"
#include "pico/multicore.h"
#include "./controll/spiPorts.h"
#include "./controll/spi.h"
#include "./controll/SDCard.h"
#include "./pio/pio.h"
#include "./pio/config.h"
#include "./errorCheck/basicError.h"
#include "./debug/printer.h"
#include "./debug/mix.h"
#include "./input/include/Stick.h"
#include <stdlib.h>


void PIOtest()
{
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &blink_program);
    printf("Loaded program at %d\n", offset);

    // init
    size_t capture_buf_size = 32;
    uint32_t capture_buf[capture_buf_size];
    blink_program_init(pio, sm, offset, 11, 1);

    // set DMA
    DMASetup(pio, sm);

    std::cout << "PIO initialized\n";

    while (true)
    {
        for (int i = 0; i < 32; i++)
        {
            // random int between 0 and 19
            capture_buf[i] = rand() % 255;
            printBits(sizeof(uint32_t), &capture_buf[i]);
        }
        dma_channel_hw_addr(DMA_CB_CHANNEL)->al3_read_addr_trig = (uintptr_t)capture_buf;
        dma_channel_wait_for_finish_blocking(DMA_CHANNEL);
    }
}

void Sticktest(){
    STICK stick;


    STICK_POSITION pos = stick.getStickPosition();
    std::cout<<"x: "<< pos.x << "y: " << pos.y << std::endl;
}
#endif