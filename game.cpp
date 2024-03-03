#include "Global.h"
#include "pico/multicore.h"

#include "./controll/spiPorts.h"
#include "./controll/spi.h"
#include "./controll/SDCard.h"

#include "./pio/vga/config.h"
#include "./pio/vga/hvga.h"
#include "./errorCheck/basicError.h"
#include "./debug/printer.h"
#include "./debug/mix.h"
#include "./input/include/Stick.h"

#include "./debug/printer.h"
#include <stdlib.h>
#include "hardware/structs/bus_ctrl.h"

//#include "./testing.h"

/*
int64_t alarm_callback(alarm_id_t id, void *user_data)
{
    // Put your timeout handler code in here
    return 0;
}
*/
int counter = 0;

void gpio_callback(uint gpio, uint32_t events)
{
}

void core1_entry()
{
    puts("core1 started");
    // gpio_set_irq_enabled_with_callback(SD_SCK_test, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
    while (1)
    {
        tight_loop_contents();
        /* code */
    }
}

int main()
{
    uint CAPTURE_N_SAMPLES = 96;
    stdio_init_all();
    sleep_ms(2000);
    set_sys_clock_khz(280000, true);
    printf("starting %d\n", clock_get_hz(clk_sys));

    //! TEST
    // Sticktest();
    //! END TEST
    /*
    multicore_launch_core1(core1_entry);

    SPIPORTS *sd_spi_ports = new SPIPORTS(SD_SPI_CHANNEL, SD_CS, SD_SCK, SD_MOSI, SD_MISO);
    SPI *spisd = new SPI(SD_FREQ, sd_spi_ports);
    SDCARD *sdCard = new SDCARD(spisd);
    */
    PIO pio = pio0;
    int smHsync = 0;
    uint offset = pio_add_program(pio, &vga_hsync_program);
    printf("Loaded program at %d\n", offset);

    // init
    size_t capture_buf_size = 32;
    uint32_t capture_buf[capture_buf_size];
    vga_hsync_program_init(pio, smHsync, offset, HSYNC);
    pio_sm_put_blocking(pio,smHsync,800);
    /*
    // set DMA
    DMASetup(pio, sm);

    puts("Hello, world!");

    pio_sm_set_enabled(pio, sm, true);
    
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
    */



    printf("End world!");

    while (true)
    {
    }
    

    return 0;
}
