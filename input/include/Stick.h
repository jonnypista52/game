#pragma once
#include "../../Global.h"

struct STICK_POSITION
{
    int x;
    int y;
};

enum dir
{
    up = 0,
    right,
    down,
    left,
    none
};

class STICK
{
private:
    // convert the raw value to a value between -100 and 100 depending on how far the stick is being pushed
    // 100-100 might not be achiveable, because the circular design.

    int stickNeutralx;
    int stickNeutraly;

public:
    STICK(/* args */);
    ~STICK();
    STICK_POSITION getStickPosition();
    //uint8_t getDirectionFromStick();
    uint16_t getThrotle();
    int8_t convertToRange(int16_t adc_raw_value, int neutralPos);
};
