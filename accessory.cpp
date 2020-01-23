#include "accessory.h"

#include <Arduino.h>

Accessory::Accessory(unsigned int const kPinOutput) : kPinOutput(kPinOutput)
{
    pinMode(kPinOutput, OUTPUT);
}

bool Accessory::GetState(void) const
{
    digitalRead(GetPinOutput());
}

void Accessory::SetState(bool const state)
{
    if(!GetLock()) {
        digitalWrite(GetPinOutput(), state);
        SetTimestampModified(millis());
    }
}
 
void Accessory::SetTimestampModified(unsigned long const timestamp_modified)
{
    timestamp_modified_ = timestamp_modified;
}
 
unsigned long Accessory::GetTimestampModified(void) const
{
    return timestamp_modified_;
}

int Accessory::GetPinOutput(void) const
{
    return kPinOutput;
}

bool Accessory::GetLock(void) const
{
    return lock_;
}

void Accessory::SetLock(bool const state)
{
    lock_ = state;
}
