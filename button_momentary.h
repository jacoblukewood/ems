// button_momentary.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef BUTTONMOMENTARY_H_
#define BUTTONMOMENTARY_H_

#include "button.h"

class ButtonMomentary : public Button {
 public:
    ButtonMomentary(int const pin_input, int const debounce, Output* const output);

    void Refresh(void);
};

#endif  // BUTTONMOMENTARY_H_
