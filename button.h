// Copyright 2020 Jacob Wood

#ifndef BUTTON_H_
#define BUTTON_H_

#include "accessory.h"
#include "engine.h"

class Button {
 public:
    enum ButtonTypes {
        kToggle,
        kMomentary,
        kPower
    };

    Button(int const kPinInput, enum Button::ButtonTypes const kButtonType, const Accessory* const output);
    Button(int const kPinInput, enum Button::ButtonTypes const kButtonType, const Engine* const engine);

    bool GetState(void) const;
    void RefreshState(void);

 private:
    static unsigned int const kDebounce = 300;  // * CONFIGURABLE * Time between button presses being recorded and being treated as new (the lower the better - increase if flickering occurs or if stop button ceases to work).
    unsigned int const kPinInput;

    Accessory* output_;
    Engine* engine_;
    ButtonTypes type_;

    unsigned long timestamp_last_pressed_;
};

#endif  // BUTTON_H_
