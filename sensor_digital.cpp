// sensor_digital.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "sensor_digital.h"

#include <Arduino.h>

#include "utility.h"

SensorDigital::SensorDigital(int const pin_input)
: Sensor(pin_input)
{ }


bool SensorDigital::GetState(void) const {
    return utility::IsDigitalInputHigh(kPinSensorInput);
}
