// ems - BMW Airhead & K Bike electronics management system.
// Copyright 2020 Jacob Wood

#include <Arduino.h>

#include "motorcycle.h"
#include "utility.h"

Motorcycle motorcycle;

void setup() {
  // Wait for valid key. The reed switch will keep the power on for this time, turning off if a key is removed.
  while (!motorcycle.rfid_seat_.Verify(kRFIDKeyList)) {
    motorcycle.display_dash_.PrintLine(Display::Symbol::ERROR, "Invalid Key", Display::Alignment::CENTER, Display::Alignment::CENTER);
  }

  // Permanently Power on EMU. Accessory mode.
  motorcycle.PowerOn();
  motorcycle.display_dash_.PrintLine(Display::Symbol::SUCCESS, "Ready", Display::Alignment::CENTER, Display::Alignment::CENTER);
}

void loop() {
  // If engine is running.
  if (motorcycle.engine_.GetState()) {
    if (motorcycle.engine_.GetRedlineState()) {
      motorcycle.display_dash_.SetLock(false);
      motorcycle.display_dash_.PrintLine(Display::Symbol::WARNING, "RPM Limit Exceeded", Display::Alignment::CENTER, Display::Alignment::CENTER);
      motorcycle.display_dash_.SetLock(true);
    } else {
      motorcycle.display_dash_.SetLock(false);
    }

    // Display odometer.
    motorcycle.display_dash_.PrintLine(Display::Symbol::NONE, String(motorcycle.odometer_.GetOdometer()), Display::Alignment::CENTER, Display::Alignment::CENTER);

    // If power button is pressed.
    if (motorcycle.button_power_.GetState()) {
      motorcycle.engine_.Stop();
      motorcycle.SetOnTime();
    }
    // If it is unsafe.
    if (motorcycle.GetStateSafety()) {
      motorcycle.engine_.Stop();
      motorcycle.SetOnTime();
      motorcycle.display_dash_.PrintLine(Display::Symbol::WARNING, "Stand Engaged", Display::Alignment::CENTER, Display::Alignment::CENTER);  // there is a bug here if 2 processes try to override the screen at once. conside adding a priority system.
    }
  } else {
  // If engine is not running.
    if (motorcycle.button_power_.GetState()) {
      // If motorcycle is safe.
      if (!motorcycle.GetStateSafety()) {
        if (!motorcycle.engine_.Start()) {
          motorcycle.SetOnTime();
          motorcycle.display_dash_.PrintLine(Display::Symbol::ERROR, "Failed to Start", Display::Alignment::CENTER, Display::Alignment::CENTER);
        }
      } else {
        motorcycle.display_dash_.PrintLine(Display::Symbol::ERROR, "Safety Issue", Display::Alignment::CENTER, Display::Alignment::CENTER);
      }
    }

    // If in accessory mode for longer than the auto-off period.
    if (utility::IntervalPassed(motorcycle.GetTimeEnterAccessory(), kAccessoryModeTimeout)) {
      motorcycle.PowerOff();
    }
  }

  // Regardless of running state
  motorcycle.AutoBrakeLight();
  motorcycle.EmergencyBrakeStrobe();

  // Check and Action Buttons
  // Brake
  motorcycle.button_brake_.RefreshState();

  // Horn
  motorcycle.button_horn_.RefreshState();

  // Indicator Left
  motorcycle.button_indicator_left_.RefreshState();

  // Indicator Right
  motorcycle.button_indicator_right_.RefreshState();

  // High Beam
  motorcycle.button_highbeam_.RefreshState();
}
