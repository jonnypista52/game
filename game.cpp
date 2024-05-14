#include "Global.h"
#include "pico/multicore.h"

#include "./controll/spiPorts.h"
#include "./controll/spi.h"
#include "./controll/SDCard.h"

#include "./vga/vga.h"

#include "./errorCheck/basicError.h"
#include "./debug/printer.h"
#include "./debug/mix.h"
#include "./input/include/Stick.h"

#include "./debug/printer.h"
#include <stdlib.h>
#include "hardware/structs/bus_ctrl.h"

// #include "./testing.h"

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
    sleep_ms(1000);
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

    VGA vga(pio1, 0, pio1, 1, pio0, 0);
    vga.fill();

    vga.startSending();

    while (true)
    {
    }

    return 0;
}
