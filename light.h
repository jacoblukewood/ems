#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "accessory.h"

class Light : public Accessory
{
public:
    Light(unsigned int const kPinOutput, unsigned int const kBrightnessLow, unsigned int const kBrightnessHigh);
    Light(unsigned int const kPinOutput);
    void SetState(bool const state);

private:
    unsigned int const kBrightnessLow_;
    unsigned int const kBrightnessHigh_;
};

#endif // LIGHT_H
