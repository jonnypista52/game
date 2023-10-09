#include <iostream>

#define X_axis_ADC 0
#define Y_axis_ADC 1
#define THROTLE_ADC 2

#define STICK_NEUTRAL 2048
#define STICK_RANGE 100

int8_t convertToRange(int16_t adc_raw_value)
{
    return ((float)(adc_raw_value - STICK_NEUTRAL) / STICK_NEUTRAL) * STICK_RANGE;
}

int main()
{

    for (int i = 0; i < 1<<12; i += 50)
    {
        std::cout << "i:" << i << " range: " << (int)convertToRange(i) << std::endl;
    }
}