#pragma once
#include "../../Global.h"


struct STICK_POSITION
{
    int x;
    int y;
};

class STICK
{
private:
    //convert the raw value to a value between -100 and 100 depending on how far the stick is being pushed
    //100-100 might not be achiveable, because the circular design.
    int8_t convertToRange(int16_t adc_raw_value);

public:
    STICK(/* args */);
    ~STICK();
    STICK_POSITION getStickPosition();
    uint16_t getThrotle();
};
