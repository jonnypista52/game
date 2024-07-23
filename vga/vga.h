#ifndef vga_h
#define vga_h

#include "./Ivga.h"
#include "../Global.h"
#include "../pio/vga/hvga.h"
#include "../pio/vga/vvga.h"
#include "../pio/vga/video.h"
#include "pico/sem.h"
#include "hardware/irq.h"

class VGA : public IVGA
{
private:
    PIO vSync;
    uint vSyncSM;
    PIO hSync;
    uint hSyncSM;
    PIO video;
    uint videoSM;

    inline static int dma_chan = 0;

    void DMASetup(PIO pio, uint sm);

public:
    explicit VGA(PIO vSync, uint vSyncSM, PIO hSync, uint hSyncSM, PIO video, uint videoSM);

    // sends the next line
    void sendNextLine() override;
    void sendBlank() override;
    void enablePIO() override;

    //! TEST
    void fill() override;
    void fillDifferent() override;
};

#endif