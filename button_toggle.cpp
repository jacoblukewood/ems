// Copyright 2020 Jacob Wood

#include "button_toggle.h"

#include <Arduino.h>

#include "utility.h"

ButtonToggle::ButtonToggle(int const pin_input, int const debounce, Accessory* const output)
: Button(pin_input, debounce, output)
{
  last_state_ = false;
}

ButtonToggle::ButtonToggle(int const pin_input, Accessory* const output)
: Button(pin_input, output)
{
  last_state_ = false;
}


void ButtonToggle::Refresh(void) {
    bool const is_pressed = utility::IsDigitalInputHigh(kPinInput);

    if (utility::IntervalPassed(time_last_pressed_, kDebounce)) {
        if(is_pressed) {
            time_last_pressed_ = millis();

            if(!was_pressed_last_refresh_) {
                if(output_->IsOn()) {
                    output_->Off();
                } else {
                    output_->On();
                }
            }

            was_pressed_last_refresh_ = true;
        } else {
            was_pressed_last_refresh_ = false;
        }
    }
}
