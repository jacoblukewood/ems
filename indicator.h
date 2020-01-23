#ifndef EMS_INDICATOR_SRC_H_
#define EMS_INDICATOR_SRC_H_

#define MILLISECONDS_PER_MINUTE 60000

#include "accessory.h"

class Indicator : public Accessory
{
public:
    Indicator(unsigned int const kFlashRate, unsigned int const kPinOutput);

    unsigned long GetTimestampCycled(void) const;
    void SetState(bool const state);
    void SetTimestampCycled(unsigned long const timestamp_cycled);

private:
    int const kFlashCycle_;

    unsigned long timestamp_cycled_;
};

#endif // EMS_INDICATOR_SRC_H_
