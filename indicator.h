#ifndef INDICATOR_H
#define INDICATOR_H
#include <Arduino.h>
#include <HardwareSerial.h>

#include "accessory.h"
#include "motorcycle.h"
#include "helper.h"

#define MILLISECONDS_PER_MINUTE 60000

class Indicator : public Accessory
{
public:
    Indicator(unsigned int const kPinOutput, unsigned int const kFlashRate, Motorcycle &motorcycle);
    void Action(bool state);
    unsigned long GetTimestampCycled(void) const;
    void SetTimestampCycled(unsigned long timestamp_cycled);

private:
    int kFlashCycle_;
    Motorcycle motorcycle_;
    unsigned long timestamp_cycled_;
};

#endif // INDICATOR_H
