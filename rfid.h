#ifndef RFID_H
#define RFID_H
#include <Arduino.h>
#include <HardwareSerial.h>

class RFID
{
private:
    unsigned int key_;

public:
    RFID(unsigned int key);
    bool Verify(void) const;
};

#endif // RFID_H