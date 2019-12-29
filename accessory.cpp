#include "accessory.h"

Accessory::Accessory(unsigned int const kPinOutput) : kPinOutput_(kPinOutput)
{
    pinMode(kPinOutput_, OUTPUT);
}

void Accessory::Action(bool state)
{
    digitalWrite(GetPinOutput(), state);
    SetTimestampModified(millis());
}

unsigned long Accessory::GetTimestampModified(void) const
{
    return timestamp_modified_;
}

void Accessory::SetTimestampModified(unsigned long timestamp_modified)
{
    timestamp_modified_ = timestamp_modified;
}

int Accessory::GetPinOutput(void) const
{
    return kPinOutput_;
}
