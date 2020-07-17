// indicator.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef INDICATOR_H_
#define INDICATOR_H_

#define MILLISECONDS_PER_MINUTE 60000

#include "light.h"

class IndicatorSet : public Accessory {
 public:
   IndicatorSet(unsigned int const flash_rate, unsigned int const pin_output, Indicator* sibling_indicator);

   void On(void);
   void Off(void);

 private:
   unsigned int const kFlashCycle;
   IndicatorSet* siblingIndicator_;

   bool state_;
};

#endif  // INDICATOR_H_
