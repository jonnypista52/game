#include "./adcmockup.h"

void adc_init() {}
void adc_gpio_init(int gpioPin) {}

void adc_select_input(int gpioPin) {}

void adc_fifo_drain() {}

int adc_read()
{
    return adcValuesArray[last_Adc_read_index];
}