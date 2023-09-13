#include "./config.h"

void DMASetup(PIO pio, uint sm, uint dma_chan, uint32_t *capture_buf, size_t capture_size_words, bool trigger_level)
{
    pio_sm_set_enabled(pio, sm, false);
    // Need to clear _input shift counter_, as well as FIFO, because there may be
    // partial ISR contents left over from a previous run. sm_restart does this.
    pio_sm_clear_fifos(pio, sm);
    pio_sm_restart(pio, sm);

    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);
    channel_config_set_dreq(&c, pio_get_dreq(pio, sm, true));

    dma_channel_configure(dma_chan, &c,
                          &pio->txf[sm],      // Destination pointer
                          capture_buf,        // Source pointer
                          capture_size_words, // Number of transfers
                          true                // Start immediately
    );
}
