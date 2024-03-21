#ifndef vga_h
#define vga_h

#include "../../Global.h"
#include "./pio/vga/hvga.h"
#include "./pio/vga/vvga.h"
#include "./pio/vga/video.h"
#include "pico/sem.h"
#include "hardware/irq.h"

// start of each value fragment (+1 for NULL terminator)
static uintptr_t fragment_start[NUM_PIXELS_INLINE + 1];

// alarm handle for handling delay
static alarm_id_t reset_delay_alarm_id;

static bool dma_hand_first = true;
static int dma_chan;
void dma_handler();


class VGA
{
private:
    PIO vSync;
    uint vSyncSM;
    PIO hSync;
    uint hSyncSM;
    PIO video;
    uint videoSM;

    size_t capture_buf_size = 32;
    uint32_t capture_buf[32];
    void DMASetup(PIO pio, uint sm);

public:
    VGA(PIO vSync, uint vSyncSM, PIO hSync, uint hSyncSM, PIO video, uint videoSM);
    ~VGA();
};

#endif