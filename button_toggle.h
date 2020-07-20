// button_toggle.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef BUTTONTOGGLE_H_
#define BUTTONTOGGLE_H_

#include "button.h"

class ButtonToggle : public Button {
 public:
    ButtonToggle(int const pin_input, int const debounce, Output* const output);

    void Refresh(void);

 private:
    bool last_state_;
};

#endif  // BUTTONTOGGLE_H_
