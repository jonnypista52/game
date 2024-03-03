#pragma once
#include "./pio/pio.h"
#include "Global.h"

class vga
{
private:
    PIO pio;
    int sm;
public:
    vga(uint8_t pio, uint8_t sm);
    ~vga();
};
