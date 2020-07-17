// utility.h
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "utility.h"

namespace utility {
bool IntervalPassed(unsigned long const start_time, unsigned int const interval) {
    return (((unsigned long)(millis() - start_time)) >= interval);  // TODO: Probably could be cleaned up. Need to test to clean.
}

unsigned long TimePassed(unsigned long const start_time) {
    return ((unsigned long)(millis() - start_time));
}

int PinMode(uint8_t pin) {
    if (pin >= NUM_DIGITAL_PINS)
        return (-1);

    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *reg = portModeRegister(port);
    if (*reg & bit)
        return (OUTPUT);

    volatile uint8_t *out = portOutputRegister(port);
    return ((*out & bit) ? INPUT_PULLUP : INPUT);
}

bool IsDigitalInputHigh(uint8_t pin) const {
    if (PinMode(pin) == INPUT_PULLUP) {
        return !digitalRead(pin);
    } else {
        return digitalRead(pin);
    }
}
}  // namespace utility
