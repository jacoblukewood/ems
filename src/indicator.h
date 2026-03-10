// indicator.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef INDICATOR_H_
#define INDICATOR_H_

#define MILLISECONDS_PER_MINUTE 60000

#include "light.h"

class Indicator : public Light {
 public:
   Indicator(unsigned int const flash_rate, unsigned int const pin_output);

   void On(void);
   void Off(void);
   void Refresh(void);

 private:
   unsigned int const kFlashCycle;
};

#endif  // INDICATOR_H_
