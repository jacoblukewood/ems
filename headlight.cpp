#include "headlight.h"

Headlight::Headlight(unsigned int const kPinOutputHeadlight, unsigned int const kPinOutputHighBeam) : Accessory(kPinOutputHeadlight), kPinOutputHighBeam_(kPinOutputHighBeam) {
    pinMode(Headlight::kPinOutputHighBeam_, OUTPUT);
}
