#include "indicator.h"

Indicator::Indicator(unsigned int const kPinOutput, unsigned int const kFlashRate, Motorcycle &motorcycle) : Accessory(kPinOutput), motorcycle_(motorcycle)
{
  kFlashCycle_ = 60000 / (kFlashRate * 2);
}

void Indicator::Action()
{
  if (motorcycle_.GetSpeed() > 15 && helper::IntervalPassed(Accessory::GetTimestampModified(), 10000))
  {
    Cancel();
    // TODO: this whole if needs fixing beause this check wont run unless the button has been pushed making it useless
  }
  else if (helper::IntervalPassed(Indicator::GetTimestampCycled(), kFlashCycle_))
  {
    digitalWrite(Indicator::GetPinOutput(), !digitalRead(Indicator::GetPinOutput()));
    Indicator::SetTimestampCycled(millis());
  }
}

unsigned long Indicator::GetTimestampCycled()
{
  return timestamp_cycled_;
}

void Indicator::SetTimestampCycled(unsigned long timestamp_cycled)
{
  timestamp_cycled_ = timestamp_cycled;
}
