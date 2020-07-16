// Copyright 2020 Jacob Wood

#include "indicator.h"

#include <Arduino.h>

#include "utility.h"

Indicator::Indicator(unsigned int const flash_rate, unsigned int const pin_output, Indicator* sibling_indicator)
: kFlashCycle(MILLISECONDS_PER_MINUTE / (flash_rate * 2))
, Light(pin_output)
, siblingIndicator_(sibling_indicator)
{ }

void Indicator::On(void) {
  siblingIndicator_->Light::Off();
  Light::On();
  state_ = true;
  // TODO: Add something to start cycling the lights.
}

void Indicator::Off(void) {
  siblingIndicator_->Light::Off();
  digitalWrite(kPinOutput, LOW);  // Not using the Light::Off() method as it will change the state property.
}

void Indicator::RefreshState(void) {
  // if (motorcycle_.GetSpeed() > kIndicatorAutoOffSpeed && utility::IntervalPassed(Accessory::GetTimestampModified(), 10000))
  // {
  //   Accessory::SetState(state);
  //   // TODO: this whole if needs fixing beause this check wont run unless the button has been pushed making it useless
  // }
  // else if (utility::IntervalPassed(Indicator::GetTimestampCycled(), kFlashCycle_))
  // {
  //   digitalWrite(Indicator::GetPinOutput(), utility::GetInputState(Indicator::GetPinOutput()));
  //   Indicator::SetTimestampCycled(millis());
  // }
}