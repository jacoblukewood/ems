#include "button.h"

Button::Button(int const kPinInput, Accessory const &output, enum Button::ButtonTypes const kButtonType) : kPinInput_(kPinInput), output_(output), type_(kButtonType)
{
  pinMode(Button::kPinInput_, INPUT_PULLUP);
}

// Button::Button(int const kPinInput, Motorcycle const &motorcycle, enum Button::ButtonTypes const kButtonType) : kPinInput_(kPinInput), motorcycle_(motorcycle), type_(kButtonType)
// {
//   pinMode(Button::kPinInput_, INPUT_PULLUP);
// }

bool Button::GetState(void) const
{
  helper::GetInputState(kPinInput_);
}

void Button::RefreshState(void)
{
  switch (type_)
  {
  case Button::ButtonTypes::kToggle:
    if (Button::GetState() && helper::IntervalPassed(timestamp_last_pressed_, kDebounce_))
    {
      output_.SetState(!output_.GetState());
    }
    break;

  case Button::ButtonTypes::kMomentary:
    output_.SetState(Button::GetState());
    break;

  case Button::ButtonTypes::kPower:
    // if (Button::GetState() && helper::IntervalPassed(timestamp_last_pressed_, kDebounce_))
    // {
    //   // TODO: Complete section.
    //   if (motorcycle_.engine_.GetState() && motorcycle_.GetStatePower())
    //   {
    //     // Test if held for 5 seconds.
    //     // Off
    //   }
    //   else
    //   {
    //     motorcycle_.engine_.Start();
    //   }
    // }
    break;
  }
}