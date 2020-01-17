#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include "accessory.h"

class Light : public Accessory
{
private:
    unsigned int kBrightnessLow_;
    unsigned int kBrightnessHigh_;

public:
    Light(unsigned int const kPinOutput, unsigned int const kBrightnessLow, unsigned int const kBrightnessHigh);
    Light(unsigned int const kPinOutput);
    void Action(bool state);
};

#endif // LIGHT_H
