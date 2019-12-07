#ifndef LIGHT_H
#define LIGHT_H
#include <Arduino.h>
#include <HardwareSerial.h>

#include "accessory.h"

class Light : public Accessory
{
private:
    unsigned int kPinOutput_;
    unsigned int state_;
    unsigned int kBrightnessLow_;

public:
    Light(unsigned int kPinOutput, unsigned int kBrightnessLow);
};

#endif // LIGHT_H
