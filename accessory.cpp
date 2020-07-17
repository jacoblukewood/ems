// Copyright 2020 Jacob Wood

#include "accessory.h"

#include <Arduino.h>

Accessory::Accessory(unsigned int const pin_output) : kPinOutput(kPinOutput) {
    pinMode(kPinOutput, OUTPUT);
}

bool Accessory::IsOn(void) const {
    digitalRead(GetPinOutput());
}

int Accessory::GetPinOutput(void) const {
    return kPinOutput;
}

void Accessory::On(void) {

}

void Accessory::Off(void) {
    
}