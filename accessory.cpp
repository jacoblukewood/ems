// Copyright 2020 Jacob Wood

#include "accessory.h"

#include <Arduino.h>

Accessory::Accessory(unsigned int const kPinOutput) : kPinOutput(kPinOutput) {
    pinMode(kPinOutput, OUTPUT);
}

bool Accessory::GetLock(void) const {
    return lock_;
}

bool Accessory::GetState(void) const {
    digitalRead(GetPinOutput());
}

int Accessory::GetPinOutput(void) const {
    return kPinOutput;
}

unsigned long Accessory::GetTimestampModified(void) const {
    return timestamp_modified_;
}

void Accessory::SetState(bool const state) {
    if (!GetLock()) {
        digitalWrite(GetPinOutput(), state);
        SetTimestampModified(millis());
    }
}

void Accessory::SetLock(bool const state) {
    lock_ = state;
}

void Accessory::SetTimestampModified(unsigned long const timestamp_modified) {
    timestamp_modified_ = timestamp_modified;
}