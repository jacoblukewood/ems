#include "button.h"

Button::Button(int const kPinInput, Accessory *output, enum Button::ButtonTypes const kButtonType) : kPinInput_(kPinInput), output_(output), type_(kButtonType)
{
  pinMode(Button::kPinInput_, INPUT_PULLUP);
}

Button::Button(int const kPinInput, Engine *engine, enum Button::ButtonTypes const kButtonType) : kPinInput_(kPinInput), engine_(engine), type_(kButtonType)
{
  pinMode(Button::kPinInput_, INPUT_PULLUP);
}

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
      output_->SetState(!output_->GetState());
    }
    break;

  case Button::ButtonTypes::kMomentary:
    output_->SetState(Button::GetState());
    break;

  case Button::ButtonTypes::kPower:
    if (Button::GetState() && helper::IntervalPassed(timestamp_last_pressed_, kDebounce_))
    {
      if (!engine_->GetState())
      {
        engine_->Start();
      }
      else
      {
        if (true) {
          // Check if held for 2 seconds. Keep in mind that the debounce is also a factor.
          engine_->Stop();
        }
      }
    }
    break;
  }
}