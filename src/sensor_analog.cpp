// sensor_analog.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "sensor_analog.h"

#include <Arduino.h>

#include "utility.h"

SensorAnalog::SensorAnalog(int const pin_input)
: Sensor(pin_input)
{ }


double SensorAnalog::GetValue(void) const {
    return analogRead(kPinSensorInput);
}
