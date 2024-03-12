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
    pio_sm_set_enabled(hSync, hSyncSM, true);
    pio_sm_set_enabled(vSync, vSyncSM, true);
    pio_sm_set_enabled(video, videoSM, true);
    // sem_init(&reset_delay_complete_sem, 1, 1); // initially posted so we don't block first time
    // DMASetup(video, videoSM);
}

VGA::~VGA()
{
}

void VGA::randomdata()
{
    printf("printing random\n");

    for (int i = 0; i < NUM_PIXELS_INLINE; i++)
    {
        fragment_start[i] = 0xFFFFFFFF;
    }
    fragment_start[NUM_PIXELS_INLINE] = 0;
    while (true)
    {
        pio_sm_put_blocking(video, videoSM, 0xFFFFFFFF);
        // printf("block sem\n");
        // sem_acquire_blocking(&reset_delay_complete_sem);
        // printf("send\n");
        // dma_channel_hw_addr(DMA_CB_CHANNEL)->al3_read_addr_trig = (uintptr_t)fragment_start;
        // printf("sent 0\n");
    }
}

void VGA::DMASetup(PIO pio, uint sm)
{
    pio_sm_set_enabled(pio, sm, false);
    // Need to clear _input shift counter_, as well as FIFO, because there may be
    // partial ISR contents left over from a previous run. sm_restart does this.
    pio_sm_clear_fifos(pio, sm);
    pio_sm_restart(pio, sm);

    dma_claim_mask(DMA_CHANNELS_MASK);

    // main DMA channel outputs 8 word fragments, and then chains back to the chain channel
    dma_channel_config channel_config = dma_channel_get_default_config(DMA_CHANNEL);
    channel_config_set_dreq(&channel_config, pio_get_dreq(pio, sm, true));
    channel_config_set_chain_to(&channel_config, DMA_CB_CHANNEL);
    channel_config_set_irq_quiet(&channel_config, true);
    dma_channel_configure(DMA_CHANNEL,
                          &channel_config,
                          &pio->txf[sm],
                          NULL, // set by chain
                          8,    // 8 words for 8 bit planes
                          false);

    // chain channel sends single word pointer to start of fragment each time
    dma_channel_config chain_config = dma_channel_get_default_config(DMA_CB_CHANNEL);
    dma_channel_configure(DMA_CB_CHANNEL,
                          &chain_config,
                          &dma_channel_hw_addr(
                               DMA_CHANNEL)
                               ->al3_read_addr_trig, // ch DMA config (target "ring" buffer size 4) - this is (read_addr trigger)
                          NULL,                      // set later
                          1,
                          false);

    irq_set_exclusive_handler(DMA_IRQ_0, dma_complete_handler);
    dma_channel_set_irq0_enabled(DMA_CHANNEL, true);
    irq_set_enabled(DMA_IRQ_0, true);
}

int64_t reset_delay_complete(alarm_id_t id, void *user_data)
{
    reset_delay_alarm_id = 0;
    sem_release(&reset_delay_complete_sem);
    printf("release sem\n");
    return 0;
}

void __isr dma_complete_handler()
{
    if (dma_hw->ints0 & DMA_CHANNEL_MASK)
    {
        // clear IRQ
        dma_hw->ints0 = DMA_CHANNEL_MASK;
        // when the dma is complete we start the reset delay timer
        if (reset_delay_alarm_id)
            cancel_alarm(reset_delay_alarm_id);
        reset_delay_alarm_id = add_alarm_in_us(400, reset_delay_complete, NULL, true);
    }
}
