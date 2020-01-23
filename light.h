// Copyright 2020 Jacob Wood

#ifndef LIGHT_H_
#define LIGHT_H_

#include "accessory.h"

class Light : public Accessory {
 public:
    Light(unsigned int const kBrightnessLow, unsigned int const kBrightnessHigh, unsigned int const kPinOutput);
    explicit Light(unsigned int const kPinOutput);

    void SetState(bool const state);

 private:
    unsigned int const kBrightnessLow;
    unsigned int const kBrightnessHigh;
};

#endif  // LIGHT_H_
