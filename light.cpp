#include "light.h"

Light::Light(unsigned int kPinOutput, unsigned int kBrightnessLow) : Accessory(kPinOutput), kPinOutput_(kPinOutput), kBrightnessLow_(kBrightnessLow)
{
}
