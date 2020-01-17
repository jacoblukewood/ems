#include "button.h"

Button::Button(int const kPinInput, Accessory *output, enum Button::ButtonTypes const kButtonType) : kPinInput_(kPinInput), output_(output), type_(kButtonType)
{
  pinMode(Button::kPinInput_, INPUT_PULLUP);
}

Button::Button(int const kPinInput, Motorcycle *motorcycle, enum Button::ButtonTypes const kButtonType) : kPinInput_(kPinInput), motorcycle_(motorcycle), type_(kButtonType)
{
  pinMode(Button::kPinInput_, INPUT_PULLUP);
}

void Button::RefreshState(void)
{
  switch (type_)
  {
  case Button::ButtonTypes::kToggle:
    if (helper::GetInputState(kPinInput_) && helper::IntervalPassed(timestamp_modified_, kDebounce_))
    {
      SetState(!GetState());
    }
    break;

  case Button::ButtonTypes::kMomentary:
    SetState(helper::GetInputState(kPinInput_));
    break;

  case Button::ButtonTypes::kPower:
    if (helper::GetInputState(kPinInput_) && helper::IntervalPassed(timestamp_modified_, kDebounce_))
    {
      // TODO: Complete section.
      if (motorcycle_->engine_.GetState() && motorcycle_->GetStatePower())
      {
        // Test if held for 5 seconds.
        // Off
      }
      else
      {
        motorcycle_->engine_.Start();
      }
    }
    break;
  }

  output_->Action(GetState());
}

bool Button::GetState(void) const
{
  return state_;
}

void Button::SetState(bool state)
{
  state_ = state;
  timestamp_modified_ = millis();
}
