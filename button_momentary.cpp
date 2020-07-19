// Copyright 2020 Jacob Wood

#include "button_momentary.h"

#include <Arduino.h>

#include "utility.h"

ButtonMomentary::ButtonMomentary(int const pin_input, int const debounce, Output* const output)
: Button(pin_input, debounce, output) {
  pinMode(Button::kPinInput, INPUT_PULLUP);
}


void ButtonMomentary::Refresh(void) {
  // Base class Button action is momentary
  
  bool const is_active = utility::IsDigitalInputHigh(kPinInput);

if(is_active != was_pressed_last_refresh_) {
  if(utility::IntervalPassed(time_last_pressed_, kDebounce)) {}
    if(output_->IsOn()) {
        output_->Off();
        was_pressed_last_refresh_ = false;
      } else {
        output_->On();
        was_pressed_last_refresh_ = true;
    }

    time_last_pressed_ = millis();
  }
}