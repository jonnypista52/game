#pragma once
#include "../../Global.h"
#include "hardware/adc.h"

// which ADC will read it, set it to 0-2, must be unique
#define X_axis_ADC 0
#define Y_axis_ADC 1
#define THROTLE_ADC 2

#define STICK_NEUTRAL 2048
#define STICK_RANGE 100

struct STICK_POSITION
{
    int x;
    int y;
};

class STICK
{
private:
    int8_t convertToRange(int16_t adc_raw_value);

public:
    STICK(/* args */);
    ~STICK();
    STICK_POSITION getStickPosition();
};
