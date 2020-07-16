// Copyright 2020 Jacob Wood

#ifndef INDICATOR_H_
#define INDICATOR_H_

#define MILLISECONDS_PER_MINUTE 60000

#include "light.h"

class Indicator : public Light {
 public:
   Indicator(unsigned int const flash_rate, unsigned int const pin_output, Indicator* sibling_indicator);

   void On(void);

 private:
   int const kFlashCycle;
   Indicator* siblingIndicator_;

   bool state_;
};

#endif  // INDICATOR_H_
