#include "./vga.h"

VGA::VGA(PIO vSync, uint vSyncSM, PIO hSync, uint hSyncSM, PIO video, uint videoSM)
{
    this->vSync = vSync;
    this->vSyncSM = vSyncSM;
    this->hSync = hSync;
    this->hSyncSM = hSyncSM;
    this->video = video;
    this->videoSM = videoSM;
    uint offsetHsync = pio_add_program(vSync, &vga_hsync_program);
    uint offsetVsync = pio_add_program(hSync, &vga_vsync_program);
    uint offsetVideo = pio_add_program(video, &vga_video_program);

    // init
    vga_hsync_program_init(hSync, hSyncSM, offsetHsync, HSYNC);
    vga_vsync_program_init(vSync, vSyncSM, offsetVsync, VSYNC);
    vga_video_program_init(video, videoSM, offsetVideo, VIDEOR0);

    pio_sm_put_blocking(hSync, hSyncSM, (640 + 48) / 16); // running a 16x extra divider
    pio_sm_put_blocking(vSync, vSyncSM, ((640 + 16 + 48) / 16) * (480 + 10 + 103));
    pio_sm_put_blocking(video, videoSM, 640 / 2);

    DMASetup(video, videoSM);

    pio_sm_set_enabled(hSync, hSyncSM, true);
    pio_sm_set_enabled(vSync, vSyncSM, true);
    pio_sm_set_enabled(video, videoSM, true);
}

VGA::~VGA()
{
}

void VGA::startSending()
{
    while (1)
    {

        // Manually call the handler once, to trigger the first transfer
        while (gpio_get(VSYNC))
            ;
        for (int currentLineSend = 0; currentLineSend < 525; currentLineSend++)
        {
            while (dma_channel_is_busy(dma_chan))
                ;
            
            if (currentLineSend > 10 && currentLineSend < 490)
            {
                dma_channel_set_read_addr(dma_chan, &genBuffer[doneLine], true);
            }
            else
            {
                dma_channel_set_read_addr(dma_chan, &blankLine, true);
            }
            dma_channel_start(dma_chan);            
        }
    }
}

///***PRIVATE ****/////

void VGA::DMASetup(PIO pio, uint sm)
{
    dma_chan = dma_claim_unused_channel(true);
    dma_chan = dma_claim_unused_channel(true);
    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    channel_config_set_read_increment(&c, false);
    channel_config_set_dreq(&c, DREQ_PIO0_TX0);

    dma_channel_configure(
        dma_chan,
        &c,
        &pio0_hw->txf[0],      // Write address (only need to set this once)
        NULL,                  // Don't provide a read address yet
        NUM_PIXELS_INLINE , // Write the same value many times, then halt and interrupt
        false                  // Don't start yet
    );
}

//***! TEST

void VGA::fill()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < NUM_PIXELS_INLINE; j++)
        {
            genBuffer[i][j] = 255;
        }
    }
}