#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>
#include <HardwareSerial.h>

namespace helper
{
/*
        * Function:  IntervalPassed
        * --------------------
        * Compares an inputted mills() start time plus an interval against the current time to see if the interval has passed.
        * 
        * start_time: a value recorded from mills() to compare the current time to.
        * interval: the amount of time in milliseconds to check if it has been since start_time.
        * 
        * returns: a boolean value as an integer - 1 (TRUE) if the interval has passed and 0 (FALSE) if it has not.
        */
bool IntervalPassed(unsigned long start_time, unsigned int interval);
unsigned long TimePassed(unsigned long start_time);
int PinMode(uint8_t pin);
bool GetInputState(uint8_t pin);
} // namespace helper

#endif // HELPER_H
