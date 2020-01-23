// Copyright 2020 Jacob Wood

#ifndef HELPER_H_
#define HELPER_H_

#include <Arduino.h>

namespace helper {
bool GetInputState(uint8_t pin);
bool IntervalPassed(unsigned long const start_time, unsigned int const interval);
int PinMode(uint8_t pin);
unsigned long TimePassed(unsigned long const start_time);
}  // namespace helper

#endif  // HELPER_H_
