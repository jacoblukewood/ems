#include "indicator.h"

Indicator::Indicator(unsigned int const kPinOutput, unsigned int const kFlashRate, Motorcycle &motorcycle) : Accessory(kPinOutput), motorcycle_(motorcycle)
{
  kFlashCycle_ = MILLISECONDS_PER_MINUTE / (kFlashRate * 2);
}

void Indicator::Action(bool state)
{
  if (motorcycle_.GetSpeed() > 15 && helper::IntervalPassed(Accessory::GetTimestampModified(), 10000))
  {
    Accessory::Action(state);
    // TODO: this whole if needs fixing beause this check wont run unless the button has been pushed making it useless
  }
  else if (helper::IntervalPassed(Indicator::GetTimestampCycled(), kFlashCycle_))
  {
    digitalWrite(Indicator::GetPinOutput(), helper::GetInputState(Indicator::GetPinOutput()));
    Indicator::SetTimestampCycled(millis());
  }
}

unsigned long Indicator::GetTimestampCycled(void) const
{
  return timestamp_cycled_;
}

void Indicator::SetTimestampCycled(unsigned long timestamp_cycled)
{
  timestamp_cycled_ = timestamp_cycled;
}
