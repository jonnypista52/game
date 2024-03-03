#ifndef vga_h
#define vga_h

#include "../../Global.h"
#include "./pio/vga/hvga.h"
#include "./pio/vga/vvga.h"

class VGA
{
private:
    /* data */
public:
    VGA(PIO vSync, uint vSyncSM, PIO hSync, uint hSyncSM);
    ~VGA();
};


#endif