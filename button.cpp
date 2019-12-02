#include "button.h"
Button::Button(int kPinInput, Accessory *output, enum Button::ButtonTypes kButtonType) : kPinInput_(kPinInput), output_(output), type_(kButtonType)
{
  pinMode(Button::kPinInput_, INPUT_PULLUP);
}

void Button::RefreshState()
{
  switch (type_)
  {
  case Button::ButtonTypes::kToggle:
    if (!digitalRead(kPinInput_) && utility::IntervalPassed(timestamp_modified_, kDebounce_))
    {
      SetState(!GetState());
    }
    break;

  case Button::ButtonTypes::kMomentary:
    SetState(!digitalRead(kPinInput_));
    break;
  }

  if (GetState())
  {
    output_->Action();
  }
  else
  {
    output_->Cancel();
  }
}

bool Button::GetState()
{
  return state_;
}

void Button::SetState(bool state)
{
  state_ = state;
  timestamp_modified_ = millis();
}
