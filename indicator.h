// Copyright 2020 Jacob Wood

#ifndef INDICATOR_H_
#define INDICATOR_H_

#define MILLISECONDS_PER_MINUTE 60000

#include "accessory.h"

class Indicator : public Accessory {
 public:
    Indicator(unsigned int const kFlashRate, unsigned int const kPinOutput);

    unsigned long GetTimestampCycled(void) const;
    void SetState(bool const state);
    void SetTimestampCycled(unsigned long const timestamp_cycled);

 private:
    int const kFlashCycle_;

    unsigned long timestamp_cycled_;
};

#endif  // INDICATOR_H_
