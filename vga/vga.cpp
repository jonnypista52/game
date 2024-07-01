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

    pio_sm_put_blocking(hSync, hSyncSM, (NUM_PIXELS_INLINE + 48) / 16); // running a 16x extra divider
    pio_sm_put_blocking(vSync, vSyncSM, ((NUM_PIXELS_INLINE + 16 + 48) / 16) * (480 + 10 + 103));
    pio_sm_put_blocking(video, videoSM, (NUM_PIXELS_INLINE) - 1);

    DMASetup(video, videoSM);

    pio_sm_set_enabled(hSync, hSyncSM, true);
    pio_sm_set_enabled(vSync, vSyncSM, true);
    pio_sm_set_enabled(video, videoSM, true);
}

VGA::~VGA()
{
}

void VGA::sendNextLine()
{
    dma_channel_set_read_addr(dma_chan, &genBuffer[doneLine], true);
    while (dma_channel_is_busy(dma_chan))
        ;
    dma_channel_start(dma_chan);
    doneLine = (doneLine + 1) % BUFFER_LINE_SIZE;
}

void VGA::sendBlank()
{
    dma_channel_set_read_addr(dma_chan, &blankLine, true);
    while (dma_channel_is_busy(dma_chan))
        ;
    dma_channel_start(dma_chan);
}

///***PRIVATE ****/////

void VGA::DMASetup(PIO pio, uint sm)
{
    dma_chan = dma_claim_unused_channel(true);
    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_read_increment(&c, true);
    channel_config_set_dreq(&c, DREQ_PIO0_TX0);

    dma_channel_configure(
        dma_chan,
        &c,
        &pio0_hw->txf[0],  // Write address (only need to set this once)
        NULL,              // Don't provide a read address yet
        NUM_PIXELS_INLINE, // Write the same value many times, then halt and interrupt
        false              // Don't start yet
    );
}

//***! TEST

void VGA::fill()
{
    for (int i = 0; i < BUFFER_LINE_SIZE; i++)
    {
        for (int j = 0; j < NUM_PIXELS_INLINE; j++)
        {
            genBuffer[i][j] = 0xD7;
        }
    }
}

void VGA::fillDifferent()
{
    for (int i = 0; i < BUFFER_LINE_SIZE; i++)
    {
        for (int j = 0; j < NUM_PIXELS_INLINE; j+=8)
        {
            genBuffer[i][j] = 0x00;
            genBuffer[i][j+1] = 0x07;
            genBuffer[i][j+2] = 0x70;
            genBuffer[i][j+3] = 0x77;
            genBuffer[i][j+4] = 0x00;
            genBuffer[i][j+5] = 0xF0;
            genBuffer[i][j+6] = 0xF7;
            genBuffer[i][j+7] = 0xFF;
        }
    }
}