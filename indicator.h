#ifndef INDICATOR_H
#define INDICATOR_H

#define MILLISECONDS_PER_MINUTE 60000

#include <Arduino.h>
#include <HardwareSerial.h>
#include "accessory.h"
#include "motorcycle.h"
#include "helper.h"

class Indicator : public Accessory
{
public:
    Indicator(unsigned int const kPinOutput, unsigned int const kFlashRate, Motorcycle &motorcycle);

    void SetState(bool const state);
    unsigned long GetTimestampCycled(void) const;
    void SetTimestampCycled(unsigned long const timestamp_cycled);

private:
    int const kFlashCycle_;
    Motorcycle motorcycle_;
    unsigned long timestamp_cycled_;
};

#endif // INDICATOR_H
