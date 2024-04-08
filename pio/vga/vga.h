#ifndef vga_h
#define vga_h

#include "../../Global.h"
#include "./pio/vga/hvga.h"
#include "./pio/vga/vvga.h"
#include "./pio/vga/video.h"
#include "pico/sem.h"
#include "hardware/irq.h"


inline static int bussyWayTooMuch = 0;

class VGA
{
private:
    inline static int dma_chan = 0;
    inline static int8_t doneLine = 0;
    PIO vSync;
    uint vSyncSM;
    PIO hSync;
    uint hSyncSM;
    PIO video;
    uint videoSM;

    inline static bool videoSync = false;
    //inline static int currentLineSend = 0;
    size_t capture_buf_size = 32;
    uint32_t capture_buf[32];
    void DMASetup(PIO pio, uint sm);

    inline static uint32_t genBuffer[3][NUM_PIXELS_INLINE]{0};
    inline static uint32_t blankLine[NUM_PIXELS_INLINE]{0};

public:
    VGA(PIO vSync, uint vSyncSM, PIO hSync, uint hSyncSM, PIO video, uint videoSM);
    ~VGA();

    //starts sending after it synced with vSync
    void startSending();

    static void dma_handler();
    //! TEST
    void fill();
};

#endif