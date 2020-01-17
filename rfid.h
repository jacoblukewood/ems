#ifndef RFID_H
#define RFID_H

#include <Arduino.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include "MFRC522.h"

class RFID
{
public:
    RFID(unsigned int const kPinSS, unsigned int const kPinRST);
    bool Verify(byte const kRFIDKeyList[][4]);

private:
    MFRC522 rfid_protocol;
};

#endif // RFID_H