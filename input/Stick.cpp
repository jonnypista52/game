#include "./include/Stick.h"

STICK::STICK(/* args */)
{
    adc_init();
    adc_gpio_init(26 + X_axis_ADC);
    adc_gpio_init(26 + Y_axis_ADC);
    adc_gpio_init(26 + THROTLE_ADC);
    adc_select_input(X_axis_ADC);
}

STICK::~STICK()
{
}

STICK_POSITION STICK::getStickPosition()
{
    adc_select_input(X_axis_ADC);
    STICK_POSITION pos;
    pos.x = convertToRange(adc_read());
    adc_select_input(Y_axis_ADC);
    pos.y = convertToRange(adc_read());
    return pos;
}

/////////////PRIVATE
int8_t STICK::convertToRange(int16_t adc_raw_value)
{
    return ((adc_raw_value - STICK_NEUTRAL) / STICK_NEUTRAL) * STICK_RANGE;
}