#ifndef EMS_LIGHT_SRC_H_
#define EMS_LIGHT_SRC_H_

#include "accessory.h"

class Light : public Accessory
{
public:
    Light(unsigned int const kBrightnessLow, unsigned int const kBrightnessHigh, unsigned int const kPinOutput);
    Light(unsigned int const kPinOutput);

    void SetState(bool const state);

private:
    unsigned int const kBrightnessLow;
    unsigned int const kBrightnessHigh;
};

#endif // EMS_LIGHT_SRC_H_
