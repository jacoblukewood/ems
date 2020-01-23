#ifndef EMS_RFID_SRC_H_
#define EMS_RFID_SRC_H_

#include "MFRC522.h"

class RFID
{
public:
    RFID(unsigned int const kPinSS, unsigned int const kPinRST);
    
    bool Verify(byte const kRFIDKeyList[][4]);

private:
    MFRC522 rfid_protocol;
};

#endif // EMS_RFID_SRC_H_