// Copyright 2020 Jacob Wood

#include "button.h"

#include <Arduino.h>

#include "utility.h"

Button::Button(int const kPinInput, enum Button::ButtonTypes const kButtonType, const Accessory *output) : kPinInput(kPinInput), type_(kButtonType), output_(output) {
  pinMode(Button::kPinInput, INPUT_PULLUP);
}

Button::Button(int const kPinInput, enum Button::ButtonTypes const kButtonType, const Engine *engine) : kPinInput(kPinInput), type_(kButtonType), engine_(engine) {
  pinMode(Button::kPinInput, INPUT_PULLUP);
}

bool Button::GetState(void) const {
  utility::GetInputState(kPinInput);
}

void Button::RefreshState(void) {
  switch (type_) {
  case Button::ButtonTypes::kToggle:
    if (Button::GetState() && utility::IntervalPassed(timestamp_last_pressed_, kDebounce)) {
      output_->SetState(!output_->GetState());
    }
    break;

  case Button::ButtonTypes::kMomentary:
    output_->SetState(Button::GetState());
    break;

  case Button::ButtonTypes::kPower:
    if (Button::GetState() && utility::IntervalPassed(timestamp_last_pressed_, kDebounce)) {
      if (!engine_->GetState()) {
        engine_->Start();
      } else {
        if (true) {
          // Check if held for 2 seconds. Keep in mind that the debounce is also a factor.
          engine_->Stop();
        }
      }
    }
    break;
  }
}
