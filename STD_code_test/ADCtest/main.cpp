#include <iostream>
#include "../../Global.h"
#include "../../input/include/Stick.h"

int main()
{
    STICK stick;
    float inputVoltage = (0.15 / 3.3) * 4096;
    float inputVoltage1 = (2.35 / 3.3) * 4096;
    float inputVoltageNeutral = (1.2 / 3.3) * 4096;

    std::cout << inputVoltage << " " << (int)stick.convertToRange(inputVoltage, inputVoltageNeutral) << std::endl;
    std::cout << inputVoltage1 << " " << (int)stick.convertToRange(inputVoltage1, inputVoltageNeutral) << std::endl;
    std::cout << inputVoltageNeutral << " " << (int)stick.convertToRange(inputVoltageNeutral, inputVoltageNeutral) << std::endl;
    STICK_POSITION tmp;

    int size = sizeof(adcValuesArray) / sizeof(adcValuesArray[0]);
    for (int i = 2; i < size; i++)
    {
        tmp = stick.getStickPosition();
        std::cout << "x: " << tmp.x << " y: " << tmp.y << std::endl;
    }

    /*
        for (int i = 0; i < 4096; i+=10)
        {
            std::cout << (int)convertToRange(i) << std::endl;
        }
    */
    return 0;
}