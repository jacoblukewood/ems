// Copyright 2020 Jacob Wood

#ifndef BUTTONTOGGLE_H_
#define BUTTONTOGGLE_H_

#include "button.h"

class ButtonToggle : public Button {
 public:
    ButtonToggle(int const pin_input, int const debounce, Accessory* const output);
    ButtonToggle(int const pin_input, Accessory* const output);

    void Refresh(void);
};

#endif  // BUTTONTOGGLE_H_
