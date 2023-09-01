#include "SDCard.h"

SDCARD::SDCARD(SPI *spi)
{
    const uint8_t dummy = 255;
    this->spi = spi;
    //send dummy data
    this->spi->cs_deselect();
    uint8_t send[10];
    for (size_t i = 0; i < 10; i++)
    {
        send[i] = 0xFF;
    }
    
    spi->write_data_continous(send,10);
    
    sleep_ms(1000);
    for(int i=0;i<10;i++){
        printf("95 CRC byte %d \n", i);
        spi->write_data_sdCard(0,0,0x95);
        spi->write_data_sdCard(0x08,0x000001AA,0x87);
        spi->write_data_sdCard(55,0,0x87);
        spi->write_data_sdCard(41,0x40000000,0x87);
    }
}

SDCARD::~SDCARD()
{
    delete this->spi;
}
