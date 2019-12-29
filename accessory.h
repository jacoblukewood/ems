#ifndef ACCESSORY_H
#define ACCESSORY_H
#include <Arduino.h>
#include <HardwareSerial.h>

class Accessory
{
public:
    Accessory(unsigned int const kPinOutput);
    virtual void Action(bool state);
    unsigned long GetTimestampModified(void) const;
    void SetTimestampModified(unsigned long timestamp_modified);
    int GetPinOutput(void) const;

private:
    unsigned int const kPinOutput_;
    unsigned long timestamp_modified_;
};

#endif // ACCESSORY_H