// Copyright 2020 Jacob Wood

#include "indicator.h"

#include <Arduino.h>

#include "helper.h"

Indicator::Indicator(unsigned int const kFlashRate, unsigned int const kPinOutput) : kFlashCycle_(MILLISECONDS_PER_MINUTE / (kFlashRate * 2)), Accessory(kPinOutput) {
}

void Indicator::SetState(bool const state) {
  // if (motorcycle_.GetSpeed() > 15 && helper::IntervalPassed(Accessory::GetTimestampModified(), 10000))
  // {
  //   Accessory::SetState(state);
  //   // TODO: this whole if needs fixing beause this check wont run unless the button has been pushed making it useless
  // }
  // else if (helper::IntervalPassed(Indicator::GetTimestampCycled(), kFlashCycle_))
  // {
  //   digitalWrite(Indicator::GetPinOutput(), helper::GetInputState(Indicator::GetPinOutput()));
  //   Indicator::SetTimestampCycled(millis());
  // }
}

unsigned long Indicator::GetTimestampCycled(void) const {
  return timestamp_cycled_;
}

void Indicator::SetTimestampCycled(unsigned long const timestamp_cycled) {
  timestamp_cycled_ = timestamp_cycled;
}
