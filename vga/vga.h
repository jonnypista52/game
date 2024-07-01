#ifndef vga_h
#define vga_h

#include "../Global.h"
#include "../pio/vga/hvga.h"
#include "../pio/vga/vvga.h"
#include "../pio/vga/video.h"
#include "pico/sem.h"
#include "hardware/irq.h"

inline static int bussyWayTooMuch = 0;

class VGA
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
    inline static int8_t doneLine = 0;     // index of buffer line in sending
    inline static int currentLineSend = 0; // scancode line

    inline static uint8_t blankLine[NUM_PIXELS_INLINE]{0};
    inline static uint8_t genBuffer[BUFFER_LINE_SIZE][NUM_PIXELS_INLINE]{0};

    VGA(PIO vSync, uint vSyncSM, PIO hSync, uint hSyncSM, PIO video, uint videoSM);
    ~VGA();

    // sends the next line
    static void sendNextLine();
    static void sendBlank();

    //! TEST
    void fill();
    void fillDifferent();
};

#endif