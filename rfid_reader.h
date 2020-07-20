// rfid_reader.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef RFIDREADER_H_
#define RFIDREADER_H_

#include "MFRC522.h"

class RFIDReader {
 public:
    RFIDReader(unsigned int const pin_ss, unsigned int const pin_rst);

    bool IsValidKeyPresent(void);

 private:
    MFRC522 rfid_protocol;

   byte keys_ [2] [4] =  // List of RFID key UIDs in hex.
   {
      {0xF9, 0xAC, 0x41, 0xC2},
      {0xF9, 0xAC, 0x41, 0xC2}
   };
};

#endif  // RFIDREADER_H_
