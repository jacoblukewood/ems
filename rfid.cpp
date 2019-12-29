#include "rfid.h"

RFID::RFID(unsigned int key)
{
    key_ = key;
}

bool RFID::Verify(void) const
{
    // TODO: Implement RFID firmware.
    // while (RFID::Read() == NULL) {
    //     if (RFID::Read() == key_) {
    //         return true;
    //     } else {
    //         return false;
    //     }
    // }
}