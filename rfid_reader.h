// rfid_reader.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood// Copyright 2020 Jacob Wood

#ifndef RFIDREADER_H_
#define RFIDREADER_H_

#include "MFRC522.h"

class RFIDReader {
 public:
    RFIDReader(unsigned int const pin_ss, unsigned int const pin_rst);

    bool IsValidKeyPresent(void);

 private:
    MFRC522 rfid_protocol;

    byte keys[][4];
};

#endif  // RFIDREADER_H_
