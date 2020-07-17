// light.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood// Copyright 2020 Jacob Wood

#include "light.h"

#include <Arduino.h>

Light::Light(unsigned int const pin_output)
: Accessory(pin_output) {
    state_ = false;
}

void Light::On(void) {
    digitalWrite(kPinOutput, HIGH);
    state_ = true;
}

void Light::Off(void) {
    digitalWrite(kPinOutput, LOW);
    state_ = false;
}
