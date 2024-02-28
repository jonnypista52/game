#include "SDCard.h"

SDCARD::SDCARD(SPI *spi)
{
    const uint8_t dummy = 255;
    this->spi = spi;
    uint8_t ret;
    // send dummy data
    uint8_t send[10];
    for (size_t i = 0; i < 10; i++)
    {
        send[i] = 0xFF;
    }
    spi->cs_deselect();
    spi->write_data_continous(send, 10);
    spi->cs_select();
    while (true)
    {
        spi->write_data_sdCard(0, 0, 0x95, &ret);
        sleep_us(100);
    }
    printf("idle\n");
    sleep_ms(1000);
    spi->write_data_sdCard(0x08, 0x000001AA, 0x87, &ret);
    spi->write_data_sdCard(55, 0, 0x87, &ret);
    spi->write_data_sdCard(41, 0x40000000, 0x87, &ret);
    spi->cs_deselect();
}

SDCARD::~SDCARD()
{
    delete this->spi;
}
