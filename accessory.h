#ifndef ACCESSORY_H
#define ACCESSORY_H
#include <Arduino.h>
#include <HardwareSerial.h>

class Accessory
{
public:
    Accessory(unsigned int const kPinOutput);
    virtual void Action();
    void Cancel();
    unsigned long GetTimestampModified() const;
    void SetTimestampModified(unsigned long timestamp_modified);
    int GetPinOutput() const;

private:
    unsigned int const kPinOutput_;
    unsigned long timestamp_modified_;
};

#endif // ACCESSORY_H