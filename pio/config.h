#ifndef pio_config_h_
#define pio_config_h_

#include "../Global.h"

void DMASetup(PIO pio, uint sm, uint dma_chan, uint32_t *capture_buf, size_t capture_size_words, bool trigger_level);

#endif