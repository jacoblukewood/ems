// Copyright 2020 Jacob Wood

#include "accessory.h"

#include <Arduino.h>

Accessory::Accessory(unsigned int const pin_output)
: kPinOutput(pin_output)
, state_(false)
{
    pinMode(kPinOutput, OUTPUT);
}

bool Accessory::IsOn(void) const {
    return state_;
}

void Accessory::On(void) {
    digitalWrite(kPinOutput, HIGH);
    lastChanged = millis();
}

void Accessory::Off(void) {
    digitalWrite(kPinOutput, LOW);
    lastChanged = millis();
}