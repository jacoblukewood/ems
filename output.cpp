// Copyright 2020 Jacob Wood

#include "output.h"

#include <Arduino.h>

Output::Output(unsigned int const pin_output)
: kPinOutput(pin_output)
, state_(false)
{
    pinMode(kPinOutput, OUTPUT);
}

bool Output::IsOn(void) const {
    return state_;
}

void Output::On(void) {
    digitalWrite(kPinOutput, HIGH);
    lastChanged = millis();
}

void Output::Off(void) {
    digitalWrite(kPinOutput, LOW);
    lastChanged = millis();
}

int Output::GetPinOutput(void) {
    return kPinOutput;
}