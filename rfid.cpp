// Copyright 2020 Jacob Wood

#include "rfid.h"

#include <Arduino.h>
#include <SPI.h>

RFID::RFID(unsigned int const kPinSS, unsigned int const kPinRST) {
    MFRC522 rfid_protocol(kPinSS, kPinRST);  // Instance of the class
    SPI.begin();  // Init SPI bus
    rfid_protocol.PCD_Init();  // Init MFRC522
}

bool RFID::Verify(byte const kRFIDKeyList[][4]) {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    rfid_protocol.PICC_IsNewCardPresent();

    // Verify if the NUID has been read
    if (rfid_protocol.PICC_ReadCardSerial()) {
        for (int i = 0; i < (sizeof &kRFIDKeyList / sizeof kRFIDKeyList[0]); i++) {
            if (rfid_protocol.uid.uidByte[0] == kRFIDKeyList[i][0] &&
                rfid_protocol.uid.uidByte[1] == kRFIDKeyList[i][1] &&
                rfid_protocol.uid.uidByte[2] == kRFIDKeyList[i][3] &&
                rfid_protocol.uid.uidByte[3] == kRFIDKeyList[i][4]) {
                return true;
            }
        }
    }

    // Halt PICC
    rfid_protocol.PICC_HaltA();

    // Stop encryption on PCD
    rfid_protocol.PCD_StopCrypto1();

    return false;
}
