#include "./spi.h"
#include "../Global.h"
#include <iostream>
using namespace std;

SPI::SPI(int frekv, SPIPORTS *portsIn) : mode(false)
{
    this->ports = portsIn;
    if (this->ports->spi)
    {
        printf("SPI 1");
        spi_Hw_inst = spi1;
    }
    else
    {
        printf("SPI 0");
        spi_Hw_inst = spi0;
    }
    spi_init(spi_Hw_inst, frekv);
    uint actual_freq_hz = spi_set_baudrate(spi_Hw_inst, frekv);
    gpio_set_function(ports->sck, GPIO_FUNC_SPI);
    gpio_set_function(ports->mosi, GPIO_FUNC_SPI);
    if (ports->miso != 0)
    {
        printf("miso pin: %d", ports->miso);
        gpio_set_function(ports->miso, GPIO_FUNC_SPI);
    }

    // Chip select is active-low, so we'll initialise it to a driven-high state
    printf("Cs pin: %d", ports->cs);
    gpio_init(ports->cs);
    gpio_set_dir(ports->cs, GPIO_OUT);
    gpio_put(ports->cs, HIGH);

    spi_set_format(spi_Hw_inst, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST);
    printf("SPI running at %u Hz\n", actual_freq_hz);
}

SPI::~SPI()
{
    delete ports;
}

void SPI::changeFormat(bool mode)
{
    this->mode = mode;
    if (mode)
        spi_set_format(spi_Hw_inst, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    else
        spi_set_format(spi_Hw_inst, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
}

void SPI::changeFormat(uint data_bits, spi_cpol_t cpol, spi_cpha_t cpha, spi_order_t order)
{
    spi_set_format(spi_Hw_inst, data_bits, cpol, cpha, order);
}
void SPI::cs_select()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(ports->cs, LOW); // Active low
    asm volatile("nop \n nop \n nop");
}
void SPI::cs_deselect()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(ports->cs, HIGH);
    asm volatile("nop \n nop \n nop");
}

void SPI::write_data(const uint8_t buffer)
{
    changeFormat(false);
    cs_select();
    spi_write_blocking(spi_Hw_inst, &buffer, 1);
    cs_deselect();
}

void SPI::write_data(const uint16_t buffer)
{
    changeFormat(true);
    cs_select();
    spi_write16_blocking(spi_Hw_inst, &buffer, 1);
    cs_deselect();
}

void SPI::write_data_sdCard(const uint8_t command, const uint32_t argument, const uint8_t CRC7, uint8_t *ret)
{
    uint8_t send[6];
    send[0] = 0x40 | command;
    send[1] = (uint8_t)((argument >> 24) & 0xFFFFFFFF);
    send[2] = (uint8_t)((argument >> 16) & 0xFFFFFFFF);
    send[3] = (uint8_t)((argument >> 8) & 0xFFFFFFFF);
    send[4] = (uint8_t)(argument & 0xFFFFFFFF);
    send[5] = CRC7;
    cs_select();
    for (size_t i = 0; i < 6; i++)
    {
        spi_write_read_blocking(spi_Hw_inst, &send[i], ret, 1);
    }
    spi_read_blocking(spi_Hw_inst, 0xff, ret, 1);
    spi_read_blocking(spi_Hw_inst, 0xff, ret, 1);
    spi_read_blocking(spi_Hw_inst, 0xff, ret, 1);
    spi_read_blocking(spi_Hw_inst, 0xff, ret, 1);
    cs_deselect();
}

void SPI::write_data_continous(const uint8_t *data, size_t len)
{
    spi_write_blocking(spi_Hw_inst, data, len);
}