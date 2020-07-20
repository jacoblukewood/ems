// button_indicator.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "button_indicator.h"

#include <Arduino.h>

#include "utility.h"

ButtonIndicator::ButtonIndicator(int const pin_input, int const debounce, Indicator* indicator_for_button, Indicator* contrasting_indicator)
: indicator_(indicator_for_button)
, contrasting_indicator_(contrasting_indicator)
, Button(pin_input, debounce, indicator_for_button)
{ }

void ButtonIndicator::Refresh(void) {
    bool const is_pressed = utility::IsDigitalInputHigh(kPinInput);

    if (utility::IntervalPassed(time_last_pressed_, kDebounce)) {
        if(is_pressed) {
            time_last_pressed_ = millis();

            if(!was_pressed_last_refresh_) {
                if(indicator_->IsOn()) {
                    indicator_->Off();
                } else {
                    indicator_->On();
                    contrasting_indicator_->Off();
                }
            }

            was_pressed_last_refresh_ = true;
        } else {
            was_pressed_last_refresh_ = false;
        }
    }
}