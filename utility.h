// utility.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#ifndef utility_H_
#define utility_H_

#include <Arduino.h>

namespace utility {
bool IsDigitalInputHigh(uint8_t pin);
bool IntervalPassed(unsigned long const start_time, unsigned int const interval);
int PinMode(uint8_t pin);
unsigned long TimePassed(unsigned long const start_time);
}  // namespace utility

#endif  // utility_H_
