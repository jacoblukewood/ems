// sensor.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "sensor.h"

#include <Arduino.h>

#include "utility.h"

Sensor::Sensor(int const pin_input)
: kPinSensorInput(pin_input)
{ }


bool Sensor::GetState(void) const {
    return utility::IsDigitalInputHigh(kPinSensorInput);
}
