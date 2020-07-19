// Copyright 2020 Jacob Wood

#ifndef BUTTONPOWER_H_
#define BUTTONPOWER_H_

#include "button.h"

class ButtonPower : public Button {
 public:
    ButtonPower(int const pin_input, int const debounce, Engine* const output, int const seconds_to_hold_to_off);

    void Refresh(void);

 private:
    bool last_state_;
    int const kSecondsToHoldToOff;
};

#endif  // BUTTONPOWER_H_
