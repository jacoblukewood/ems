// button_power.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "button_power.h"

#include <Arduino.h>

#include "utility.h"

ButtonPower::ButtonPower(int const pin_input, int const debounce, Engine* const output, int const seconds_to_hold_to_off)
: Button(pin_input, debounce, output)
, kSecondsToHoldToOff(seconds_to_hold_to_off)
{
  last_state_ = false;
}


void ButtonPower::Refresh(void) {
    if (utility::IsDigitalInputHigh(kPinInput)) {
        if (!was_pressed_last_refresh_) {
            time_last_pressed_ = millis();
        }

        if (utility::IntervalPassed(time_last_pressed_, kSecondsToHoldToOff)) {
            output_->Off();
        }

        was_pressed_last_refresh_ = true;
    } else {
        was_pressed_last_refresh_ = false;
    }
}
