// stand.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include <Arduino.h>
#include <Wire.h>

#include "stand.h"

Stand::Stand(int const pin_sensor_input)
: SensorDigital(pin_sensor_input)
{ }


bool Stand::IsLowered(void) const {
  return GetState();
}