#include "./spiPorts.h"

SPIPORTS::SPIPORTS(
    int spi,
    int cs,
    int sck,
    int mosi) : spi(spi), cs(cs), sck(sck), mosi(mosi) {}

SPIPORTS::SPIPORTS(
    int spi,
    int cs,
    int sck,
    int mosi,
    int miso) : spi(spi), cs(cs), sck(sck), mosi(mosi), miso(miso) {}
