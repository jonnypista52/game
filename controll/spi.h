#pragma once

#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "./spiPorts.h"

class SPI
{
private:
    SPIPORTS *ports;
    spi_inst_t *spi_Hw_inst;
    bool mode;

public:
    SPI(int frekv, SPIPORTS *ports);
    ~SPI();

    //* if true then it sets SPI to write 16 bit
    //* else outputs 8 bit only
    void changeFormat(const bool mode);
    void changeFormat(uint data_bits, spi_cpol_t cpol, spi_cpha_t cpha, spi_order_t order);
    //set cs low
    void cs_select();
    //set cs high
    void cs_deselect();
    void write_data(const uint8_t buffer);
    void write_data(const uint16_t buffer);

    void write_data_sdCard(const uint8_t command, const uint32_t argument, const uint8_t CRC7, uint8_t* ret);

    void write_data_continous(const uint8_t* data, size_t len);

    //* DEBUG
    void printer();
};
