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
    if(!IsLocked()) {
        digitalWrite(kPinOutput, HIGH);
        timeLastChanged_ = millis();
    }
}

void Output::Off(void) {
    if(!IsLocked()) {
        digitalWrite(kPinOutput, LOW);
        timeLastChanged_ = millis();
    }
}

void Output::Lock(void) {
    allow_state_modification_ = false;
}


void Output::Unlock(void) {
    allow_state_modification_ = true;
}

bool Output::IsLocked(void) {
    return allow_state_modification_;
}

int Output::GetPinOutput(void) {
    return kPinOutput;
}