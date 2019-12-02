#include "taillight.h"

TailLight::TailLight(unsigned int kPinOutputTailLight, unsigned int kTailLightBrightness) : Accessory(kPinOutputTailLight), kPinOutputTailLight_(kPinOutputTailLight), kTailLightBrightness_(kTailLightBrightness)
{
}
