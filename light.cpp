// Copyright 2020 Jacob Wood

#include "light.h"

#include <Arduino.h>

Light::Light(unsigned int const kBrightnessLow, unsigned int const kBrightnessHigh, unsigned int const kPinOutput) : kBrightnessLow(kBrightnessLow), kBrightnessHigh(kBrightnessHigh), Accessory(kPinOutput) {
}

Light::Light(unsigned int const kPinOutput) : Accessory(kPinOutput), kBrightnessLow(0), kBrightnessHigh(255) {
}

void Light::SetState(bool const state) {
    if (!GetLock()) {
        analogWrite(GetPinOutput(), state ? kBrightnessHigh : kBrightnessLow);
        SetTimestampModified(millis());
    }
}
