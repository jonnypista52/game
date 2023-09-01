#pragma once

class SPIPORTS
{
public:
    int spi;
    int cs;
    int sck;
    int mosi;
    int miso = 0;
    SPIPORTS(
        int spi,
        int cs,
        int sck,
        int mosi);
    SPIPORTS(
        int spi,
        int cs,
        int sck,
        int mosi,
        int miso);

    ~SPIPORTS() {}
};
