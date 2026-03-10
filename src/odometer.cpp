// odometer.cpp
// github.com/jacoblukewood/ems
// Copyright 2020 Jacob Wood

#include "odometer.h"

#include <Arduino.h>
#include <EEPROM.h>

Odometer::Odometer(unsigned int eeprom_odometer_address)
: kEEPROMOdometerAddress(eeprom_odometer_address)
, kOdometerStart(EEPROM.get(eeprom_odometer_address, meters_traveled_since_last_save_)) {
    // Stored in meters
    meters_traveled_since_last_save_ = 0;
}


void Odometer::SaveOdometerToEEPROM() {
    EEPROM.put(kEEPROMOdometerAddress, (kOdometerStart + meters_traveled_since_last_save_));
}


void Odometer::AddMetersToOdometer(float meters_to_add) {
    meters_traveled_since_last_save_ += meters_to_add;
}


float Odometer::GetOdometer(void) {
    return (kOdometerStart + meters_traveled_since_last_save_) / 1000;  // Returns the odometer in km   // TODO: Fix magic number
}
