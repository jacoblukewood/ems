// indicator.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "indicator.h"

#include <Arduino.h>

#include "utility.h"

Indicator::Indicator(unsigned int const flash_rate, unsigned int const pin_output)
: kFlashCycle(MILLISECONDS_PER_MINUTE / (flash_rate * 2))
, Light(pin_output)
{ }


void Indicator::On(void) {
  state_ = true;
  Refresh();
  // TODO: Add something to start cycling the lights.
}


void Indicator::Off(void) {
  state_ = false;
  Refresh();
}


void Indicator::Refresh(void) {
  if(IsOn()) {
    if(millis() > (lastChanged + kFlashCycle)) {
      Light::On();
    }
  } else {
    Light::Off();
  }
  // if (motorcycle_.GetSpeed() > kIndicatorAutoOffSpeed && utility::IntervalPassed(Output::GetTimestampModified(), 10000))
  // {
  //   Output::SetState(state);
  //   // TODO: this whole if needs fixing beause this check wont run unless the button has been pushed making it useless
  // }
  // else if (utility::IntervalPassed(Indicator::GetTimestampCycled(), kFlashCycle_))
  // {
  //   digitalWrite(Indicator::GetPinOutput(), utility::GetInputState(Indicator::GetPinOutput()));
  //   Indicator::SetTimestampCycled(millis());
  // }
}