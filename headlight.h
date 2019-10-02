#ifndef HEADLIGHT_H
#define HEADLIGHT_H
#include <arduino.h>
#include <HardwareSerial.h>

#include "accessory.h"

class Headlight: public Accessory {
public:
    Headlight(unsigned int const kPinOutputHeadlight, unsigned int const kPinOutputHighBeam);

private:
    unsigned int const kPinOutputHighBeam_;
};

#endif // HEADLIGHT_H
