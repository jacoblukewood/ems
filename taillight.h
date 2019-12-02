#ifndef TAILIGHT_H
#define TAILIGHT_H
#include <Arduino.h>
#include <HardwareSerial.h>

#include "accessory.h"

class TailLight : public Accessory
{
private:
    unsigned int kPinOutputTailLight_;
    unsigned int state_;
    unsigned int kTailLightBrightness_;

public:
    TailLight(unsigned int kPinOutputTailLight, unsigned int kTailLightBrightness);
};

#endif // TAILIGHT_H
