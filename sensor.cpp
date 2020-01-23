#include "sensor.h"

#include <Arduino.h>

#include "helper.h"

Sensor::Sensor(int const kPinInput) : kPinInput_(kPinInput)
{
}

bool Sensor::GetState(void) const
{
    return helper::GetInputState(kPinInput_);
}