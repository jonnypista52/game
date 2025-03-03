#include <iostream>
#include "../../Global.h"

int convertToRange(int16_t adc_raw_value)
{
    return ((float)(adc_raw_value - STICK_NEUTRAL) / STICK_NEUTRAL) * STICK_RANGE;
}

int main()
{

    float inputVoltage = (0.15 / 3.3) * 4096;
    float inputVoltage1 = (2.35 / 3.3) * 4096;
    float inputVoltageNeutral = (1.2 / 3.3) * 4096;

    std::cout << inputVoltage << " " << (int)convertToRange(inputVoltage) << std::endl;
    std::cout << inputVoltage1 << " " << (int)convertToRange(inputVoltage1) << std::endl;
    std::cout << inputVoltageNeutral << " " << (int)convertToRange(inputVoltageNeutral) << std::endl;
    /*
        for (int i = 0; i < 4096; i+=10)
        {
            std::cout << (int)convertToRange(i) << std::endl;
        }
    */
    return 0;
}