#include <iostream>
#include "../../Global.h"
#include "../../input/include/Stick.h"


STICK stick;

enum dir getDirectionFromStick()
{

    STICK_POSITION tmp;
    tmp = stick.getStickPosition();
    std::cout << "x: " << tmp.x << " y: " << tmp.y << " dir: ";
    if (tmp.x > STICK_binary_treshold)
        return up;
    if (tmp.y > STICK_binary_treshold)
        return right;
    // convert negative to positive, if it would been a big pistivite value then it
    // would have already exited
    if ((tmp.x * -1) > STICK_binary_treshold)
        return down;
    if ((tmp.y * -1) > STICK_binary_treshold)
        return left;
    return none;
}

int main()
{

    float inputVoltage = (0.15 / 3.3) * 4096;
    float inputVoltage1 = (2.35 / 3.3) * 4096;
    float inputVoltageNeutral = (1.2 / 3.3) * 4096;

    std::cout << inputVoltage << " " << (int)stick.convertToRange(inputVoltage, inputVoltageNeutral) << std::endl;
    std::cout << inputVoltage1 << " " << (int)stick.convertToRange(inputVoltage1, inputVoltageNeutral) << std::endl;
    std::cout << inputVoltageNeutral << " " << (int)stick.convertToRange(inputVoltageNeutral, inputVoltageNeutral) << std::endl;
    STICK_POSITION tmp;

    int size = sizeof(adcValuesArray) / sizeof(adcValuesArray[0]);
    for (int i = 2; i < size; i += 2)
    {
        // tmp = stick.getStickPosition();

        std::cout << getDirectionFromStick() << std::endl;
    }

    /*
        for (int i = 0; i < 4096; i+=10)
        {
            std::cout << (int)convertToRange(i) << std::endl;
        }
    */
    return 0;
}