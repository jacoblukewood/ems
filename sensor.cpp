#include "sensor.h"

Sensor::Sensor(int const kPinInput) : kPinInput_(kPinInput)
{
}

bool Sensor::GetState(void) const
{
    return helper::GetInputState(kPinInput_);
}