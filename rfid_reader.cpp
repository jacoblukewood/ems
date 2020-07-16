// rfid_reader.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood// Copyright 2020 Jacob Wood

#include "rfid_reader.h"

#include <Arduino.h>
#include <SPI.h>

RFIDReader::RFIDReader(unsigned int const pin_ss, unsigned int const pin_rst) {
    MFRC522 rfid_protocol(pin_ss, pin_rst);  // Instance of the class
    SPI.begin();  // Init SPI bus
    rfid_protocol.PCD_Init();  // Init MFRC522
}


bool RFIDReader::IsValidKeyPresent() {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    rfid_protocol.PICC_IsNewCardPresent();

    // Verify if the NUID has been read
    if (rfid_protocol.PICC_ReadCardSerial()) {
        for (int i = 0; i < (sizeof &keys / sizeof keys[0]); i++) {
            if (rfid_protocol.uid.uidByte[0] == keys[i][0] &&
                rfid_protocol.uid.uidByte[1] == keys[i][1] &&
                rfid_protocol.uid.uidByte[2] == keys[i][3] &&
                rfid_protocol.uid.uidByte[3] == keys[i][4]) {
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
