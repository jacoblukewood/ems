#include "light.h"

Light::Light(unsigned int const kPinOutput, unsigned int const kBrightnessLow, unsigned int const kBrightnessHigh) : Accessory(kPinOutput), kBrightnessLow_(kBrightnessLow), kBrightnessHigh_(kBrightnessHigh)
{
}

Light::Light(unsigned int const kPinOutput) : Accessory(kPinOutput), kBrightnessLow_(0), kBrightnessHigh_(255)
{
}

void Light::SetState(bool const state)
{
    if (!GetOverride())
    {
        analogWrite(GetPinOutput(), state ? kBrightnessHigh_ : kBrightnessLow_);
        SetTimestampModified(millis());
    }
}
