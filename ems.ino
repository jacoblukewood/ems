// ems - BMW Airhead & K Bike electronics management system.
// Copyright 2020 Jacob Wood

#include <Arduino.h>

#include "motorcycle.h"
#include "utility.h"

Motorcycle motorcycle;

void setup() {
  // Wait for valid key. The reed switch will keep the power on for this time, turning off if a key is removed.
  while (!motorcycle.rfid_reader_.IsValidKeyPresent()) {  // While loop will block code from proceeding until key is found.
    motorcycle.display_dash_.PrintLine(Display::Symbol::ERROR, "Invalid Key", Display::Alignment::CENTER, Display::Alignment::CENTER);
  }

  // Permanently Power on EMU. Accessory mode.
  motorcycle.PowerOn();
}

void loop() {
  if (motorcycle.engine_.IsRunning()) {
    motorcycle.display_dash_.PrintLine(Display::Symbol::SUCCESS, "Ready", Display::Alignment::CENTER, Display::Alignment::CENTER);

    if (motorcycle.engine_.IsRedlining()) {
      motorcycle.display_dash_.PrintLine(Display::Symbol::WARNING, "RPM Limit Exceeded", Display::Alignment::CENTER, Display::Alignment::CENTER);
      motorcycle.display_dash_.Lock();
    } else {
      motorcycle.display_dash_.Unlock();
    }

    // Display odometer.
    motorcycle.display_dash_.PrintLine(Display::Symbol::NONE, String(motorcycle.odometer_.GetOdometer()), Display::Alignment::CENTER, Display::Alignment::CENTER);

    // if (motorcycle.button_power_.GetState()) {
    //   motorcycle.engine_.Stop();
    //   motorcycle.SetOnTime();
    // }

    if (!motorcycle.IsSafeToRide()) {
      motorcycle.engine_.Stop();
      // motorcycle.SetOnTime();
      motorcycle.display_dash_.PrintLine(Display::Symbol::WARNING, "Stand Engaged", Display::Alignment::CENTER, Display::Alignment::CENTER);  // there is a bug here if 2 processes try to override the screen at once. conside adding a priority system.
    }
  } else {
    // If engine is not running.
    // if (utility::IntervalPassed(motorcycle.GetTimeEnterAccessory(), motorcycle.GetAccessoryModeTimeout())) {  // If in accessory mode for longer than the auto-off period.
    //   motorcycle.PowerOff();
    // }
  }

  // Regardless of running state
  // motorcycle.AutoBrakeLight();
  // motorcycle.EmergencyBrakeStrobe();

  motorcycle.RefreshButtons();
}