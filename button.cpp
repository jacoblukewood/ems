// Copyright 2020 Jacob Wood

#include "button.h"

#include <Arduino.h>

#include "utility.h"

Button::Button(int const pin_input, int const debounce, Accessory* const output)
: kPinInput(pin_input)
, kDebounce(debounce)
, output_(output) {
  pinMode(Button::kPinInput, INPUT_PULLUP);
  last_state_ = false;
}

Button::Button(int const pin_input, Accessory* const output)
: Button(pin_input, 300, output)
{ }


void Button::Refresh(void) {
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
}