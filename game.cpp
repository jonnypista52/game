#include "Global.h"
#include "pico/multicore.h"
#include "./controll/spiPorts.h"
#include "./controll/spi.h"
#include "./controll/SDCard.h"
#include "./pio/pio.h"
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
    if (counter == 48)
    {
        printf("\n");
        counter = 0;
    }
    counter++;
    printf("CS %d, sck: %d, MOSI: %d, MISO %d\n", gpio_get(SD_CS_test), gpio_get(SD_SCK_test), gpio_get(SD_MOSI_test), gpio_get(SD_MISO_test));
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
    stdio_init_all();
    sleep_ms(2000);
    set_sys_clock_48mhz();
    //set_sys_clock_khz(280000, true);
    printf("starting %d\n", clock_get_hz(clk_sys));

    /*
    multicore_launch_core1(core1_entry);

    SPIPORTS *sd_spi_ports = new SPIPORTS(SD_SPI_CHANNEL, SD_CS, SD_SCK, SD_MOSI, SD_MISO);
    SPI *spisd = new SPI(SD_FREQ, sd_spi_ports);
    SDCARD *sdCard = new SDCARD(spisd);
    */

    // Timer example code - This example fires off the callback after 2000ms
    // add_alarm_in_ms(2000, alarm_callback, NULL, false);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &blink_program);
    printf("Loaded program at %d\n", offset);

    blink_program_init(pio, sm, offset, 11, 1);
        
    puts("Hello, world!");
    while (1)
    {
        tight_loop_contents();
        /* code */
    }

    return 0;
}
