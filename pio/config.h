#ifndef pio_config_h_
#define pio_config_h_

#include "../Global.h"
#include "pico/sem.h"

// bit plane content dma channel
#define DMA_CHANNEL 0
// chain channel for configuring main dma channel to output from disjoint 8 word fragments of memory
#define DMA_CB_CHANNEL 1

#define DMA_CHANNEL_MASK (1u << DMA_CHANNEL)
#define DMA_CB_CHANNEL_MASK (1u << DMA_CB_CHANNEL)
#define DMA_CHANNELS_MASK (DMA_CHANNEL_MASK | DMA_CB_CHANNEL_MASK)

// posted when it is safe to output a new set of values
static struct semaphore reset_delay_complete_sem;
// alarm handle for handling delay
static alarm_id_t reset_delay_alarm_id;

void DMASetup(PIO pio, uint sm);

void __isr dma_complete_handler();

int64_t reset_delay_complete(alarm_id_t id, void *user_data) ;
#endif