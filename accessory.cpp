#include "accessory.h"

Accessory::Accessory(unsigned int const kPinOutput) : kPinOutput_(kPinOutput) {
    pinMode(kPinOutput_, OUTPUT);
}

void Accessory::Action() {
   digitalWrite(GetPinOutput(), HIGH);
   SetTimestampModified(millis());
}

void Accessory::Cancel() {
   digitalWrite(GetPinOutput(), LOW);
   SetTimestampModified(millis());
}

unsigned long Accessory::GetTimestampModified() const {
    return timestamp_modified_;
}

void Accessory::SetTimestampModified(unsigned long timestamp_modified) {
    timestamp_modified_ = timestamp_modified;
}

int Accessory::GetPinOutput() const {
    return kPinOutput_;
}
