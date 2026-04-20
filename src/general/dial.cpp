#include "dial.h"



Dial::Dial(uint8_t attachTo, uint8_t resolution, uint16_t min, uint16_t max, bool useFilter)
{
    init(attachTo, resolution, min, max, useFilter);
}

void Dial::init(uint8_t attachTo, uint8_t resolution, uint16_t min, uint16_t max, bool useFilter)
{
    // #ifdef CONFIG_IDF_TARGET_ESP32

    // _pin = attachTo;

    // #endif
}