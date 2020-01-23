// Copyright 2020 Jacob Wood

#include "odometer.h"

#include <Arduino.h>
#include <EEPROM.h>

Odometer::Odometer(unsigned int kEEPROMOdometerAddress) : kEEPROMOdometerAddress(kEEPROMOdometerAddress), kOdometerStart(EEPROM.get(kEEPROMOdometerAddress, odometer_trip_)) {
    // Stored in meters
    odometer_trip_ = 0;
}

void Odometer::SaveOdometer() {
    EEPROM.put(kEEPROMOdometerAddress, (kOdometerStart + odometer_trip_));
}

void Odometer::AddOdometer(int value) {
    odometer_trip_ += value;
}

float Odometer::GetOdometer(void) {
    return (kOdometerStart + odometer_trip_) / 1000;  // Returns the odometer in km
}
