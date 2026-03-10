// button.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef BUTTON_H_
#define BUTTON_H_

#include "output.h"
#include "engine.h"

class Button {
 public:
    Button(int const pin_input, int const debounce, Output* const output)
    : kPinInput(pin_input)
    , kDebounce(debounce)
    , output_(output)
    { }

    virtual void Refresh(void) = 0;

 protected:
    Output* const output_;

    unsigned int const kDebounce;  // * CONFIGURABLE * Time between button presses being recorded and being treated as new (the lower the better - increase if flickering occurs or if stop button ceases to work).
    unsigned int const kPinInput;

    unsigned long time_last_pressed_;

    bool was_pressed_last_refresh_;
};

#endif  // BUTTON_H_
