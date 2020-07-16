// // Copyright 2020 Jacob Wood

// #include "button.h"

// #include <Arduino.h>

// #include "utility.h"

// ButtonIndicator::ButtonIndicator(int const kPinInput, enum Button::ButtonTypes const kButtonType, const Accessory *output) : kPinInput(kPinInput), type_(kButtonType), output_(output) {
//   pinMode(Button::kPinInput, INPUT_PULLUP);
// }

// void ButtonIndicator::RefreshState(void) {
//   switch (type_) {
//   case Button::ButtonTypes::kTwoButton:
//     if (Button::GetState() && utility::IntervalPassed(timestamp_last_pressed_, kDebounce)) {
//       output_->SetState(!output_->GetState());
//     }
//     break;

//   case Button::ButtonTypes::kThreeButton:
//     if (Button::GetState() && utility::IntervalPassed(timestamp_last_pressed_, kDebounce)) {
//       output_->SetState(!output_->GetState());
//     }
//     break;
//   }
// }