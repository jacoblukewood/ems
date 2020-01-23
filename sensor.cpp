#include "sensor.h"

#include <Arduino.h>

#include "helper.h"

Sensor::Sensor(int const kPinInput) : kPinInput(kPinInput)
{
}

bool Sensor::GetState(void) const
{
    return helper::GetInputState(kPinInput);
}