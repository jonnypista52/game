#ifndef adcmockup_h
#define adcmockup_h


//list of values and will read in order, adc select ignored
static int adcValuesArray[]{2028,2028,0,0,0,1000,0,3000,0,4020,1000,0,3000,0,4020,0,1000,1000,1000,3000};
static int last_Adc_read_index = 0;
void adc_init(); // doesn't have to do anything

void adc_gpio_init(int gpioPin);

void adc_select_input(int gpioPin);

void adc_fifo_drain();

int adc_read();

#endif